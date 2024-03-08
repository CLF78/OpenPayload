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

    // Get the full aid map and the corresponding bit mask
    RKNetController::Sub* sub = RKNetController::instance->getCurrentSub();
    u32 aidMap = sub->availableAids | (1 << sub->myAid);

    // Get the list of aids that have not completed the loading procedure
    RKNetSELECTHandler* sel = RKNetSELECTHandler::instance;
    u32 incompleteAids = ~(sel->aidsWithNewSelect &
                           sel->aidsWithNewRH1 &
                           sel->aidsWithNewRaceSettings &
                           sel->aidsThatHaveVoted &
                           sel->aidsWithAccurateAidPidMap);

    // Remove unused bits
    incompleteAids &= aidMap;
    DEBUG_REPORT("[WIIMMFI_KICK] Detected room stall with AIDs %08X\n", incompleteAids)

    // Kick each user still lingering
    for (int i = 0; i < 12; i++) {
        if (incompleteAids >> i & 1)
            Kick::ScheduleForAID(i);
    }
}

} // namespace RoomStall
} // namespace Wiimmfi
