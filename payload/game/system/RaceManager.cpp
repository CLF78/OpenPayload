#include <common/Common.hpp>
#include <game/kart/KartObjectManager.hpp>
#include <game/race/RaceGlobals.hpp>
#include <game/system/CourseMap.hpp>
#include <game/system/RaceConfig.hpp>
#include <game/system/RaceManager.hpp>
#include <wiimmfi/Reporting.hpp>
#include <ModSupport.hpp>

////////////////////////
// Ultra Shortcut Fix //
////////////////////////

// RaceManager::Player::updateCheckpoint() patch
// Disable ultra shortcuts in online worldwide races
// Credits: Chadderz, MrBean35000vr
kmHookFn bool UltraUncut(float requiredCompletion, MapdataCheckPoint* currCkpt, MapdataCheckPoint* nextCkpt) {

	// Check if it's a start line check point
	if (currCkpt->mpData->lapCheck == 0) {

		// If the previous key checkpoint is not 1 and the feature is enabled, always decrement the lap
		if (nextCkpt->prevKcpId > 1 && ModSupport::AreUltraShortcutsEnabled())
			return false;

		// Original check
    	for (int i = 0; i < nextCkpt->nextCount; i++) {
        	if (currCkpt->id == nextCkpt->nextCheckPoints[i].checkpoint->id)
            	return false;
    	}
	}

	// Ensure at least 5% of the lap is completed
	return (requiredCompletion >= -0.95f);
}

// Glue code
kmCallDefAsm(0x805350DC) {
    nofralloc

    // Push stack
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)

    // Call C++ code
    fmr f1, f30
    mr r3, r28
    mr r4, r29
    bl UltraUncut

    // Determine the exit address based on the bool return value
    // Return 0 to run regular check -> returns to 80535154
    // Return 1 to skip the next checks -> returns to 805351DC
    mulli r3, r3, 0x88
    addi r3, r3, 0x74
    lwz r4, 0x14(r1)
    add r3, r3, r4

    // Pop stack and return
    mtlr r3
    addi r1, r1, 0x10
    blr
}

///////////////////////
// Wiimmfi Telemetry //
///////////////////////

// RaceManager::calc() patch
// Report race finish
// Credits: Wiimmfi
kmBranchDefCpp(0x8053369C, NULL, void) {

    // Check if the race is online
    if (!RaceGlobals::isOnlineRace)
        return;

    // Check if the race is finished
    u32 raceStage = RaceManager::instance->raceStage;
    if (raceStage != RaceManager::STAGE_FINISH_ALL)
        return;

    // Report it
    Wiimmfi::Reporting::ReportRaceStage(raceStage);
}

// RaceManager::Player::endRace() patch
// Report finish times
// Credits: Wiimmfi
kmCallDefCpp(0x8053490C, void, u8 playerIdx) {

    // Check if the race is online and if so send the data
    if (RaceGlobals::isOnlineRace)
        Wiimmfi::Reporting::ReportFinishTime(playerIdx);

    // Original call
    KartObjectManager::endRace(playerIdx);
}
