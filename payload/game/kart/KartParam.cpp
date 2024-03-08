#include <common/Common.hpp>
#include <game/race/RaceGlobals.hpp>
#include <wiimmfi/Reporting.hpp>

///////////////////////
// Wiimmfi Telemetry //
///////////////////////

// KartParam::Init() patch
// Report Common.szs subfile hashes for potential cheating
// Credits: Wiimmfi
kmBranchDefCpp(0x80591B70, NULL, void) {
    if (RaceGlobals::isOnlineRace)
        Wiimmfi::Reporting::ReportCommonSubfiles();
}
