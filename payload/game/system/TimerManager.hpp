#include <common/Common.hpp>
#include <game/system/Timer.hpp>
#include <game/util/Random.hpp>

class TimerManager {
public:
    virtual ~TimerManager();
    virtual void reset();
    virtual void calc();

    Timer timers[3];
    Random random;

    bool raceTimeout;
    bool raceStarted;
    bool timerReversed;
    // 1 byte padding

    u32 raceDurationMillis;
    s32 raceFrameCounter;
    u32 _4C; // unused
};
size_assert(TimerManager, 0x50);
