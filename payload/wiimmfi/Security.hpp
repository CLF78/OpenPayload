#include <common/Common.hpp>
#include <game/net/packet/RKNetRacePacketHeader.hpp>

namespace Wiimmfi {
namespace Security {

    // Validates a RACE packet to prevent invalid data from being transmitted
    // This function assumes a full packet header, adjust checks accordingly
    // Returns true if valid
    bool ValidateRACEPacket(u32 aid, RKNetRACEPacketHeader* data, u32 dataLength);

} // namespace Security
} // namespace Wiimmfi
