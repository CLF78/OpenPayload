#include <common/Common.hpp>

namespace Wiimmfi {
namespace Delay {

    ///////////////
    // Functions //
    ///////////////

    // Calculates the delay
    void Calc(u32 frameCount);

    // Applies the delay to the given timer
    u32 Apply(u32 timer);

    ///////////////
    // Variables //
    ///////////////

    // The time the match started
    extern u32 sMatchStartTime;

    // The delay accumulated during the entire match
    extern u32 sCumulativeDelay;

    // The delay accumulated between the latest two frames
    extern u32 sCurrentDelay;

} // namespace Delay
} // namespace Wiimmfi
