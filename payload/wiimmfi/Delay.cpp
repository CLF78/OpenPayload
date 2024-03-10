#include <common/Common.hpp>
#include <gs/common/gsPlatformUtil.h>
#include <DolphinDevice.hpp>

namespace Wiimmfi {
namespace Delay {

u32 sMatchStartTime;
u32 sCumulativeDelay;
u32 sCurrentDelay;

u32 GetTime() {

    // If we are on Dolphin, use the IOCTL
    if (DolphinDevice::Open()) {
        u32 time = DolphinDevice::GetElapsedTime();
        return (time != 0) ? time : current_time();
    }

    // Else just use the game function
    return current_time();
}

void Calc(u32 frameCount) {

    // Do not do anything if the frame count is 0
    if (frameCount == 0)
        return;

    // If the match start time is not set, do so
    if (sMatchStartTime == 0)
        sMatchStartTime = GetTime();

    // Calculate the total frames elapsed since race start
    u32 timeElapsed = GetTime() - sMatchStartTime;
    float framesElapsed = timeElapsed / (1000.0f / 60.0f);
    u32 framesElapsed32 = (u32)framesElapsed;

    // Calculate the delay
    int delay = framesElapsed32 - frameCount - sCumulativeDelay;
    if (delay > 0) {
        sCurrentDelay = delay;
        DEBUG_REPORT("[WIIMMFI_TIME] Detected delay of %d frames\n", delay);
    }
}

u32 Apply(u32 timer) {

    // Get the current delay and transfer it to the cumulative delay
    int currDelay = sCurrentDelay;
    sCumulativeDelay += currDelay;

    // Reset the current delay and return the updated timer
    sCurrentDelay = 0;
    return timer + currDelay + 1;
}

} // namespace Delay
} // namespace Wiimmfi
