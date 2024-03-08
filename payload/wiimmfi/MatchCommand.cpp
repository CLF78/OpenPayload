#include <common/Common.hpp>
#include <dwc/dwc_main.h>
#include <dwc/dwc_match.h>
#include <dwc/dwc_node.h>
#include <gs/gt2/gt2Main.h>
#include <gs/gt2/gt2Utility.h>
#include <platform/stdio.h>
#include <platform/string.h>
#include <revolutionex/net/NETDigest.h>
#include <wiimmfi/ConnectionMatrix.hpp>
#include <wiimmfi/MatchCommand.hpp>

namespace Wiimmfi {
namespace MatchCommand {

void ProcessRecvConnFailMtxCommand(int clientAPid, u32 clientAIP, u16 clientAPort, DWCMatchCommandConnFailMtx* data, int dataLen) {

    // Only process the command if we are waiting
    // This should also act as a host check since this state cannot be in use by a client (i think)
    if (stpMatchCnt->state != DWC_MATCH_STATE_SV_WAITING) {
        DEBUG_REPORT("[WIIMMFI_RECV] But ignored (invalid state)\n")
        return;
    }

    // Ensure the data size is correct
    if (DWC_MATCH_CMD_GET_ACTUAL_SIZE(dataLen) != sizeof(*data)) {
        DEBUG_REPORT("[WIIMMFI_RECV] But ignored (invalid data size)\n")
        return;
    }

    // Find a "client B" with a connection failure, as we can only send the commands once per function
    // Q: Why can't we just find the lowest AID instead of running the entire loop everytime?
    int clientBAid = -1;
    for (int i = 0; i < 0xC; i++) {
        if (data->connFailMtx >> i & 1)
            clientBAid = i;
    }

    // If no "client B" was found, bail
    if (clientBAid == -1) {
        DEBUG_REPORT("[WIIMMFI_RECV] But ignored (no connection failures)\n")
        return;
    }

    // Get node info for client A and client B
    // Check for null and eventually bail
    DWCNodeInfo* clientAInfo = DWCi_NodeInfoList_GetNodeInfoForProfileId(clientAPid);
    DWCNodeInfo* clientBInfo = DWCi_NodeInfoList_GetNodeInfoForAid(clientBAid);
    if (!clientAInfo || !clientBInfo) {
        DEBUG_REPORT("[WIIMMFI_RECV] But ignored (invalid PID/AID)\n")
        return;
    }

    // Copy the node info to the temporary new node
    // Q: Why is this necessary?
    memcpy(&stpMatchCnt->tempNewNodeInfo, clientBInfo, sizeof(DWCNodeInfo));

    // Set up the command for client B and send it
    DWCMatchCommandNewPidAid cmd;
    NETWriteSwappedBytes32(&cmd.pid, stpMatchCnt->tempNewNodeInfo.profileId);
    NETWriteSwappedBytes32(&cmd.aid, stpMatchCnt->tempNewNodeInfo.aid);
    DWCi_SendMatchCommand(DWC_MATCH_CMD_NEW_PID_AID, clientAPid, clientAIP, clientAPort,
                          &cmd, DWC_MATCH_CMD_GET_SIZE(sizeof(cmd)));

    // Send a SYN packet to client A
    DWCi_SendMatchSynPacket(clientAInfo->aid, DWC_MATCH_SYN_CMD_SYN);

    // Reset node info and return
    memset(&stpMatchCnt->tempNewNodeInfo, 0, sizeof(DWCNodeInfo));
}

void ProcessRecvConnMtxCommand(int srcPid, DWCMatchCommandConnMtx* data, int dataLen) {

    // Ensure the data size is correct
    if (DWC_MATCH_CMD_GET_ACTUAL_SIZE(dataLen) != sizeof(*data)) {
        DEBUG_REPORT("[WIIMMFI_RECV] But ignored (invalid data size)\n")
        return;
    }

    // If the profile id of the source client isn't found, reset the outdated matrices
    DWCNodeInfo* node = DWCi_NodeInfoList_GetNodeInfoForProfileId(srcPid);
    if (node) Wiimmfi::ConnectionMatrix::sRecvConnMtx[node->aid] = data->connMtx;
    else Wiimmfi::ConnectionMatrix::ResetRecv();
}

bool ProcessRecvMatchCommand(u8 cmd, int profileId, u32 publicIp, u16 publicPort, void* cmdData, int dataLen) {

    // Dispatch call to different functions depending on the command
    // Use the original function as a fallback
    switch(cmd) {

        case DWC_MATCH_CMD_CONN_FAIL_MTX:
            DEBUG_REPORT("[WIIMMFI_RECV] Received CONN_FAIL_MTX command\n")
            ProcessRecvConnFailMtxCommand(profileId, publicIp, publicPort,
                                          (DWCMatchCommandConnFailMtx*)cmdData, dataLen);
            return true;

        case DWC_MATCH_CMD_CONN_MTX:
            DEBUG_REPORT("[WIIMMFI_RECV] Received CONN_MTX command\n")
            ProcessRecvConnMtxCommand(profileId, (DWCMatchCommandConnMtx*)cmdData, dataLen);
            return true;

        default:
            return false;
    }
}

void SendConnFailMtxCommand(u32 aidsConnectedToHost, u32 aidsConnectedToMe) {

    // Get the AIDs who haven't connected to me
    DWCMatchCommandConnFailMtx cmd;
    cmd.connFailMtx = aidsConnectedToHost & ~aidsConnectedToMe;

    // If all AIDs are connected or i am waiting, bail
    if (!cmd.connFailMtx || stpMatchCnt->state == DWC_MATCH_STATE_CL_WAITING)
        return;

    // Get the host's node info, with all the necessary failsaves
    DWCNodeInfo* hostNodeInfo = DWCi_NodeInfoList_GetServerNodeInfo();
    if (!hostNodeInfo || hostNodeInfo->profileId == 0)
        return;

    // Send the command
    DEBUG_REPORT("[WIIMMFI_SEND] Sending CONN_MTX command with data %08X\n", cmd.connFailMtx)
    DWCi_SendMatchCommand(DWC_MATCH_CMD_CONN_FAIL_MTX, hostNodeInfo->profileId, hostNodeInfo->publicip,
                          hostNodeInfo->publicport, &cmd, DWC_MATCH_CMD_GET_SIZE(sizeof(cmd)));
}

void SendConnMtxCommand(u32 aidsConnectedToMe) {

    // Failsafe
    if (stpMatchCnt->nodeInfoList.nodeCount == 0)
        return;

    // Set up the command
    DWCMatchCommandConnMtx cmd;
    cmd.connMtx = aidsConnectedToMe;
    DEBUG_REPORT("[WIIMMFI_SEND] Sending CONN_FAIL_MTX command with data %08X\n", aidsConnectedToMe)

    // Send the command to every node
    for (int i = 0; i < stpMatchCnt->nodeInfoList.nodeCount; i++) {

        // Get the node and check that it isn't me
        DWCNodeInfo* node = &stpMatchCnt->nodeInfoList.nodeInfos[i];
        if (node->profileId == stpMatchCnt->profileId)
            continue;

        // Send the command
        DWCi_SendMatchCommand(DWC_MATCH_CMD_CONN_MTX, node->profileId, node->publicip, node->publicport,
                              &cmd, DWC_MATCH_CMD_GET_SIZE(sizeof(cmd)));
    }
}

} // namespace Natneg
} // namespace Wiimmfi
