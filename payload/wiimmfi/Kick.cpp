#include <common/Common.hpp>
#include <dwc/dwc_main.h>
#include <dwc/dwc_match.h>
#include <nw4r/ut/Lock.hpp>
#include <platform/string.h>
#include <wiimmfi/Kick.hpp>

namespace Wiimmfi {
namespace Kick {

u32 sAidsToBeKicked = 0;
bool sMustEndRace = false;

void ScheduleForAID(int aid) {
    DEBUG_REPORT("[WIIMMFI_KICK] Scheduled kick for aid %d\n", aid)
    sAidsToBeKicked |= (1 << aid);
}

void ScheduleForEveryone() {
    DEBUG_REPORT("[WIIMMFI_KICK] Scheduled kick for all aids\n")
    sAidsToBeKicked = 0xFFFFFFFF;
}

void CalcKick() {

    // If the aid bitfield is empty, bail
    if (!sAidsToBeKicked)
        return;

    // Lock interrupts
    nw4r::ut::AutoInterruptLock lock;
    DEBUG_REPORT("[WIIMMFI_KICK] Running kick task with aids %08X\n", sAidsToBeKicked)

    // If the bitfield is full, close all connections immediately
    if (sAidsToBeKicked == 0xFFFFFFFF)
        DWC_CloseAllConnectionsHard();

    // Otherwise kick each aid separately
    else {
        for (int i = 0; i < 12; i++) {
            if (sAidsToBeKicked >> i & 1)
                DWC_CloseConnectionHard(i);
        }
    }

    // Reset the bitfield
    sAidsToBeKicked = 0;
}

int ParseKickMessage(GPConnection conn, char* data) {

    // Ignore kick commands if we don't have the necessary structures
    if (!stpMatchCnt || stpMatchCnt->nodeInfoList.nodeCount > 1)
        return GP_ERROR_NONE;

    // If the kick command isn't found, bail
    char* kickCmd = strstr(data, KICK_MSG);
    if (!kickCmd)
        return GP_ERROR_NONE;

    // Obtain the kick type
    strshift(kickCmd, KICK_MSG);
    u32 kickType = strtoul(kickCmd, nullptr, 10);
    DEBUG_REPORT("[WIIMMFI_KICK] Received kick type ", kickType)

    // Act based on the kick type
    switch (kickType) {

        // Use CloseConnectionHard to kick everyone (HOST ONLY)
        case EVERYONE:
            DEBUG_REPORT("EVERYONE\n")
            if (!DWC_IsServerMyself()) {
                DEBUG_REPORT("[WIIMMFI_KICK] But ignored (not host).\n")
                break;
            }

            ScheduleForEveryone();
            break;

        // Pretend to cause a network error and kick ourselves
        case SELF:
            DEBUG_REPORT("SELF\n")
            DWCi_HandleGPError(GP_ERROR_NETWORK);
            return GP_ERROR_MEMORY;

        // Force end the race
        case END_RACE:
            DEBUG_REPORT("END_RACE\n")
            sMustEndRace = true;
            break;

        // Kick a specific player (HOST ONLY)
        case SPECIFIC_PLAYER:
            DEBUG_REPORT("PLAYER\n")
            if (!DWC_IsServerMyself()) {
                DEBUG_REPORT("[WIIMMFI_KICK] But ignored (not host).\n")
                break;
            }

            // Get the kickpid parameter, if not found bail
            char* pidKickParam = strstr(kickCmd, KICK_MSG_PARAM_PID);
            if (!pidKickParam) {
                DEBUG_REPORT("[WIIMMFI_KICK] But ignored (no PID specified).\n")
                break;
            }

            // Shift the string and read the pid to an integer
            strshift(pidKickParam, KICK_MSG_PARAM_PID);
            u32 pidToKick = strtoul(pidKickParam, nullptr, 10);

            // Get the node info
            // If it exists, kick the corresponding aid
            DWCNodeInfo* node = DWCi_NodeInfoList_GetNodeInfoForProfileId(pidToKick);
            if (!node) {
                DEBUG_REPORT("[WIIMMFI_KICK] But ignored (AID not found).\n")
                break;
            }

            ScheduleForAID(node->aid);
            break;

        default:
            DEBUG_REPORT("UNKNOWN (%d)\n", kickType);
    }

    return GP_ERROR_NONE;
}

} // namespace Kick
} // namespace Wiimmfi
