#include <common/Common.hpp>
#include <game/system/CourseMap.hpp>
#include <game/system/RaceConfig.hpp>
#include <wiimmfi/Delay.hpp>
#include <wiimmfi/Kick.hpp>
#include <wiimmfi/Reporting.hpp>

///////////////////////
// Wiimmfi Telemetry //
///////////////////////

// RaceScene::createSubsystems() patch
// Hash and report various course subfiles
// Credits: Wiimmfi
kmCallDefCpp(0x805543A4, void, CourseMap* self) {

    // If we're online, send the data
    // We cannot use the isOnline variable since it hasn't been initialized yet
    if (RaceConfig::instance->raceScenario.settings.isOnline())
        Wiimmfi::Reporting::ReportCourseSubfiles();

    // Original call
    self->init();
}

/////////////////////
// Wiimmfi Various //
/////////////////////

// RaceScene::createSubsystems() patch
// Reset various values before the race begins
kmBranchDefCpp(0x80554728, NULL, void) {
    Wiimmfi::Reporting::sTargetFrameCount = 0;
    Wiimmfi::Kick::sMustEndRace = false;
    Wiimmfi::Delay::sMatchStartTime = 0;
    Wiimmfi::Delay::sCumulativeDelay = 0;
    Wiimmfi::Delay::sCurrentDelay = 0;
}
