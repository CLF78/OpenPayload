#include <common/Common.hpp>
#include <game/net/RKNetController.hpp>
#include <game/net/packet/RKNetRoomPacket.hpp>
#include <game/net/packet/RKNetSelectPacket.hpp>
#include <wiimmfi/Security.hpp>
#include <ModSupport.hpp>

namespace Wiimmfi {
namespace Security {

// TODO rewrite with worldwide support
bool IsPacketSectionSizeValid(int section, u32 sectionSize) {

    // Skip empty sections
    if (sectionSize == 0)
        return true;

    // The check depends on each section
    u32 destSize = RKNetController::packetBufferSizes[section];
    switch (section) {

        // For EVENT packets, ensure the size fits the buffer as it is variable
        case RKNetRACEPacketHeader::EVENT:
            return sectionSize <= destSize;

        // For ROOM/SELECT packets, ensure the size matches one of the two possible values
        case RKNetRACEPacketHeader::ROOM_SELECT:
            return (sectionSize == sizeof(RKNetROOMPacket) || sectionSize == sizeof(RKNetSELECTPacket));

        // For RACEDATA and ITEM packets, ensure the size is either half or the full buffer size
        case RKNetRACEPacketHeader::RACEDATA:
        case RKNetRACEPacketHeader::ITEM:
            return (sectionSize == destSize / 2 || sectionSize == destSize);

        // For all other sections, match exactly the default size
        default:
            return sectionSize == destSize;
    }
}

// Code ported from WiiLink24's WFC patcher
bool ValidateRACEPacket(u32 aid, RKNetRACEPacketHeader* data, u32 dataLength) {

    // Verify each section size is valid
    // Do this separately as the sizes may be valid but may not add up
    u32 expectedPacketSize = 0;
    for (int i = 0; i < RKNetRACEPacketHeader::SECTION_COUNT; i++) {
        expectedPacketSize += data->sizes[i];
        if (!IsPacketSectionSizeValid(i, data->sizes[i]))
            return false;
    }

    // Ensure the declared sizes match the cumulative size
    if (dataLength < expectedPacketSize)
        return false;

    // Verify each section's data is valid
    u8* packetData = (u8*)data;
    for (int i = 0; i < RKNetRACEPacketHeader::SECTION_COUNT; i++) {
        if (!ModSupport::IsPacketSectionDataValid(i, packetData, data->sizes[i]))
            return false;

        packetData += data->sizes[i];
    }

    // All checks passed, we're ready to go!
    return true;
}

} // namespace Security
} // namespace Wiimmfi
