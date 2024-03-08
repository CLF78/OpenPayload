#include <common/Common.hpp>
#include <dwc/dwc_main.h>
#include <dwc/dwc_match.h>
#include <wiimmfi/ConnectionMatrix.hpp>
#include <wiimmfi/MatchCommand.hpp>
#include <wiimmfi/Natneg.hpp>
#include <wiimmfi/Reporting.hpp>
#include <ModSupport.hpp>

///////////////////////////
// Custom Match Commands //
///////////////////////////

kmHookFn int ProcessRecvMatchCommand(u8 cmd, int profileId, u32 publicIp, u16 publicPort, void* cmdData, int dataLen) {

    // Check if the Wiimmfi payload can parse the command
    if (Wiimmfi::MatchCommand::ProcessRecvMatchCommand(cmd, profileId, publicIp, publicPort, cmdData, dataLen))
        return 0;

    // Check the mod's custom function
    if (ModSupport::ProcessRecvMatchCommand(cmd, profileId, publicIp, publicPort, cmdData, dataLen))
        return 0;

    // Fall back to game code
    return DWCi_ProcessRecvMatchCommand(cmd, profileId, publicIp, publicPort, cmdData, dataLen);
}

// DWCi_MatchGPRecvBuddyMsgCallback() patch
// Parse custom match commands coming from GPCM
// Credits: Wiimmfi
kmCall(0x800D94F0, ProcessRecvMatchCommand);

// DWCi_HandleGT2UnreliableMatchCommandMessage() patch
// Parse custom match commands coming from another client
// Credits: Wiimmfi
kmCall(0x800E5980, ProcessRecvMatchCommand);

// DWCi_QR2ClientMsgCallback() patch
// Parse custom match commands coming from MASTER
// Credits: Wiimmfi
kmCall(0x800E5B14, ProcessRecvMatchCommand);

/////////////////
// Fast NATNEG //
/////////////////

// DWCi_MatchProcess() patch
// Replace Nintendo's algorithm to pick the next node to NATNEG with
// Credits: Wiimmfi
kmHookFn DWCNodeInfo* GetNextMeshMakingNode() {
    return Wiimmfi::Natneg::GetNextMeshMakingNode();
}

// Glue code
kmBranchDefAsm(0x800D80D0, 0x800D8360) {
    nofralloc

    // Call C++ code
    bl GetNextMeshMakingNode

    // Move result to r31 and check for null at the same time
    mr. r31, r3
    blr
}

// Replace the exit point branch destination
kmWrite32(0x800D8360, 0x4082FE3C);

// DWCi_ProcessMatchSynPacket() patch
// Parse SYN packets in more states than normally allowed
// Credits: Wiimmfi
kmCallDefAsm(0x800D9754) {
    nofralloc

    // Original check
    cmpwi r0, DWC_MATCH_STATE_CL_WAITING
    beqlr

    // Extra check
    cmpwi r0, DWC_MATCH_STATE_CL_SYN
    blr
}

// DWCi_ProcessMatchPollingPacket() patch
// Send DWC_CMD_CONN_FAIL_MTX command to speed up NATNEG
// Credits: Wiimmfi
kmHookFn u32 SendConnFailMtxCmd(u32 aidsConnectedToHost) {

    // Get the AIDs connected to me and eventually send the command
    u32 aidsConnectedToMe = DWC_GetAIDBitmap();
    Wiimmfi::MatchCommand::SendConnFailMtxCommand(aidsConnectedToHost, aidsConnectedToMe);

    // Get the dead AID bitmap for the game code
    return aidsConnectedToMe & ~aidsConnectedToHost;
}

// Glue code
kmBranchDefAsm(0x800DA7D0, 0x800DA7DC) {
    nofralloc

    // Call C++ code
    mr r3, r30
    bl SendConnFailMtxCmd

    // Move result to r29 and match null check from game code
    mr. r29, r3
    blr
}

// DWCi_ProcessMatchSynTimeout() patch
// Change the SYN-ACK timeout to 7 seconds instead of 5 seconds per node
// Credits: Wiimmfi
kmWrite32(0x800E1A58, 0x38C00000 | 7000);

// DWCi_ProcessMatchSynTimeout() patch
// Try to recover from a SYN-ACK timeout (i think)
// Credits: Wiimmfi
kmBranchDefCpp(0x800E1CA8, NULL, bool, bool ret) {
    Wiimmfi::Natneg::RecoverSynAckTimeout();
    return ret;
}

// DWCi_NNCompletedCallback() patch
// Do not count repeated NATNEG failures between the host and a client towards the Error 86420 counter
// Credits: Wiimmfi
kmHookFn bool PreventRepeatNATNEGFail() {
    return Wiimmfi::Natneg::PreventRepeatNATNEGFail(stpMatchCnt->tempNewNodeInfo.profileId);
}

// Glue code
kmBranchDefAsm(0x800E6778, 0x800E6780) {
    nofralloc

    // Call C++ code
    bl PreventRepeatNATNEGFail

    // Restore r7
    lis r7, stpMatchCnt@ha
    lwz r7, stpMatchCnt@l(r7)

    // Check that the return value is 0 to use the following game code
    cmpwi r3, 0
    blr
}

/////////////////////////////////////
// Fast NATNEG / Wiimmfi Telemetry //
/////////////////////////////////////

// DWCi_PostProcessConnection() patch
// Update the connection matrix when a new connection is made
// Credits: Wiimmfi
kmBranch(0x800E09A8, Wiimmfi::ConnectionMatrix::Update);

///////////////////////////////////////
// Match Command Buffer Overflow Fix //
///////////////////////////////////////

// DWCi_HandleGT2UnreliableMatchCommandMessage() patch
// Ignore match commands coming from another client bigger than 0x80 bytes
// Credits: WiiLink24
kmCallDefAsm(0x800E5924) {
    nofralloc

    // Original check
    cmplw r31, r0
    bnelr

    // Check that the command fits the buffer (ASM generated from Godbolt)
    // C++ equivalent: bool r3 = (r5 + 0x14) > 0x80;
    // The result is compared to zero to reuse the beq instruction after the hook address
    subi r3, r5, (0x80 - 0x14 + 1)
    nor r3, r3, r5
    srwi. r3, r3, 31
    blr
}

// DWCi_QR2ClientMsgCallback() patch
// Ignore match commands coming from MASTER bigger than 0x80 bytes
// Credits: WiiLink24
kmCallDefAsm(0x800E5AAC) {
    nofralloc

    // Original check
    cmplwi r0, 0x5A
    bnelr

    // Get the data size
    lbz r5, 0x11(r1)

    // Check that the command fits the buffer (ASM generated from Godbolt)
    // C++ equivalent: bool r3 = (r5 + 0x14) > 0x80;
    // The result is compared to zero to reuse the beq instruction after the hook address
    subi r3, r5, (0x80 - 0x14 + 1)
    nor r3, r3, r5
    srwi. r3, r3, 31
    blr
}

////////////////////////
// NATNEG Suspend Fix //
////////////////////////

// DWCi_RequestSuspendMatchAsync() patch
// Attempt to fix the "suspend bug", where DWC stalls suspending the match due
// to ongoing NATNEG between clients. This patch will ignore NATNEG and suspend
// anyway if not the host.
// Credits: WiiLink24, MrBean35000vr
kmCallDefAsm(0x800E77F4) {
    nofralloc

    lbz r0, 0x16(r31) // Get stpMatchCnt->hostState
    cmpwi r0, 0 // Not in a match
    beqlr // r0 = 0 will already fall through to 0x800E7814

    cmpwi r0, 1 // Client in room
    beqlr // r0 = 1 will already fall through to 0x800E781C

    lwz r0, 0x71C(r31); // Get stpMatchCnt->state
    blr
}

///////////////////////
// Wiimmfi Telemetry //
///////////////////////

// DWCi_ProcessRecvMatchCommand() and DWCi_SendServerDownQuery() patches
// Report host disconnections to the server
kmHookFn int ReportHostDisconnect(u8 cmd, int pid, u32 publicIp, u32 publicPort, u32* data, u32 dataLen) {
    int ret = DWCi_SendMatchCommand(cmd, pid, publicIp, publicPort, data, dataLen);
    Wiimmfi::Reporting::ReportServerDown(cmd, pid, data);
    return ret;
}

// Glue code
kmCall(0x800DDF40, ReportHostDisconnect);
kmCall(0x800DE1E4, ReportHostDisconnect);
kmCall(0x800E6A14, ReportHostDisconnect);
