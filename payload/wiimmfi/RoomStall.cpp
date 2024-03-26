#include <common/Common.hpp>
#include <game/net/RKNetController.hpp>
#include <game/net/RKNetSelectHandler.hpp>
#include <wiimmfi/Kick.hpp>
#include <wiimmfi/RoomStall.hpp>

namespace Wiimmfi {
namespace RoomStall {

u16 sKickTimer;

void Init() {
    sKickTimer = 0;
}

void Update() {

    // Check if the player is the host, if not bail
    if (!RKNetController::instance->isPlayerHost())
        return;

    // Update the timer and check that it hasn't reached the threshold
    if (sKickTimer++ < KICK_THRESHOLD_TIME)
        return;

    // Reset the timer if the threshold is reached
    sKickTimer = 0;

    // Get the full aid map
    RKNetController::Sub* sub = RKNetController::instance->getCurrentSub();
    RKNetSELECTHandler* sel = RKNetSELECTHandler::instance;
    u32 aidMap = sub->availableAids | (1 << sub->myAid);

    // Get the list of aids that have not completed the loading procedure, depending on the phase
    u32 incompleteAids = 0;
    switch(sel->sendPacket.phase) {

        case RKNetSELECTPacket::PREPARE:
            incompleteAids = (~sel->aidsWithNewSelect) & aidMap;
            if (incompleteAids == 0)
                incompleteAids = (~sel->aidsWithNewRaceSettings) & aidMap;
            break;

        case RKNetSELECTPacket::VOTING:
            incompleteAids = (~sel->aidsThatHaveVoted) & aidMap;
            if (incompleteAids == 0)
                incompleteAids = (~sel->aidsWithVoteData) & aidMap;
            break;

        default:
            break;
     }

    // Kick the AIDs
    DEBUG_REPORT("[WIIMMFI_KICK] Detected room stall with AIDs %08X\n", incompleteAids)
    Kick::ScheduleForAIDs(incompleteAids);
}

} // namespace RoomStall
} // namespace Wiimmfi
