#include <common/Common.hpp>
#include <game/system/RaceConfig.hpp>
#include <game/system/RaceModeOnlineVs.hpp>
#include <wiimmfi/Kick.hpp>
#include <ModSupport.hpp>

///////////////////////////////////////////
// Time Limit Modifier / Wiimmfi Kicking //
///////////////////////////////////////////

// RaceModeOnlineVs::calc() patch
// Add extra conditions to end the race
// Credits: Chadderz, Wiimmfi
kmBranchDefCpp(0x8053F39C, 0x8053F444, void, RaceModeOnlineVs* self) {

    // Original function call
    // No need to trigger the race finish if the 30 second timer has run out
    if (self->tryEndRaceAfterLeaderFinish())
        return;

    // If we are in live view mode, don't do anything
    if (RaceConfig::instance->raceScenario.settings.cameraMode == RaceConfig::Settings::CAMERA_MODE_LIVE_VIEW)
        return;

    // Run the modified check
    // TODO custom reason for Wiimmfi-mandated race end?
    if (self->manager->timerManager->timers[0].getTimeMs() > ModSupport::GetOnlineTimeLimit() || Wiimmfi::Kick::sMustEndRace)
        self->endLocalRaceWithReason(4);
}
