#include <common/Common.hpp>

class Timer {
public:
    virtual ~Timer();

    u32 getTimeMs() { return milliseconds + seconds * 1000 + minutes * 60 * 1000; }

    u16 minutes;
    u8 seconds;
    u16 milliseconds;
    bool active;
};
size_assert(Timer, 0xC);
