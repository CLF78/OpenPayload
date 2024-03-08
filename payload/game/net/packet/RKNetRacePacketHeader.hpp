#include <common/Common.hpp>

struct RKNetRACEPacketHeader {

    enum Section {
        HEADER,
        RACEHEADER_1,
        RACEHEADER_2,
        ROOM_SELECT,
        RACEDATA,
        USER,
        ITEM,
        EVENT,
        SECTION_COUNT,
    };

    u32 empty;
    u32 checksum;
    u8 sizes[SECTION_COUNT];
};
size_assert(RKNetRACEPacketHeader, 0x10);
