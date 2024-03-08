#include <common/Common.hpp>

namespace Wiimmfi {
namespace RoomStall {

    ///////////////
    // Constants //
    ///////////////

    // The timer before stalled users are kicked, in frames
    static const int KICK_THRESHOLD_TIME = 90 * 60;

    ///////////////
    // Functions //
    ///////////////

    // Initializes the room stall timer
    void Init();

    // Updates the room stall timer and kicks players if necessary
    void Update();

} // namespace RoomStall
} // namespace Wiimmfi
