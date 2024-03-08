#include <common/Common.hpp>
#include <game/net/packet/RKNetRoomPacket.hpp>

class RKNetROOMHandler {
public:
    enum ROOMRole {
        ROOM_HOST,
        ROOM_GUEST,
    };

    // TODO change this to RKNetROOMPacket if the packet gets expanded
    void SetAllSendPackets(u32 packet);

    bool statusDataSet;
    ROOMRole role;
    RKNetROOMPacket sendPackets[12];
    RKNetROOMPacket recvPackets[12];
    u8 lastSendAid;
    s64 lastSendTimestamp;
    s64 _78; // unused

    static RKNetROOMHandler* instance;
};
size_assert(RKNetROOMHandler, 0x80);
