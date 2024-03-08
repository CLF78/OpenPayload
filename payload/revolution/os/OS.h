#include <common/Common.h>
#include <revolution/os/OSLoMem.h>

#ifdef __cplusplus
extern "C" {
#endif

// Round API
#define OSRoundUp32B(x) (((u32)(x) + 32 - 1) & ~(32 - 1))
#define OSRoundDown32B(x) (((u32)(x)) & ~(32 - 1))

// Interrupt API
BOOL OSDisableInterrupts();
BOOL OSEnableInterrupts();
BOOL OSRestoreInterrupts(BOOL interrupts);

// Clock API
#define OS_BUS_CLOCK __OSBusClockSpeed
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)

#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))
#define OSTicksToMicroseconds(ticks) (((ticks) * 8) / (OS_TIMER_CLOCK / 125000))
#define OSTicksToNanoseconds(ticks) (((ticks) * 8000) / (OS_TIMER_CLOCK / 125000))

#define OSSecondsToTicks(sec) ((sec) * OS_TIMER_CLOCK)
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)
#define OSNanosecondsToTicks(nsec) (((nsec) * (OS_TIMER_CLOCK / 125000)) / 8000)

u32 OSGetTick();
s64 OSGetTime();

inline void OSWait(u32 ticks) {
    u32 tick0 = OSGetTick();
    u32 tick1;
    do {
        tick1 = OSGetTick();
    } while (tick1 - tick0 < ticks);
}

#ifdef __cplusplus
}
#endif
