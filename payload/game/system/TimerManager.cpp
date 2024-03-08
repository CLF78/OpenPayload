#include <common/Common.hpp>
#include <game/race/RaceGlobals.hpp>
#include <wiimmfi/Delay.hpp>

/////////////////////////
// Wiimmfi Timekeeping //
/////////////////////////

// TimerManager::calc() patch
// Account for lag when updating the frame counter in online race
// Credits: Wiimmfi
kmCallDefCpp(0x80535C78, u32, u32 timer) {
    return (RaceGlobals::isOnlineRace) ? Wiimmfi::Delay::Apply(timer) : timer + 1;
}

// Glue code
kmWrite8(0x80535C7D, 0x7D);
