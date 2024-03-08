#include <common/Common.hpp>
#pragma pack(push, 1)

struct RKNetROOMPacket {
    enum MessageType {
        MSG_NONE,
        MSG_ROOM_START,        // param1: event type, param2: none
        MSG_REGISTER_FRIEND,   // param1: none, param2: none
        MSG_JOIN,              // param1: none, param2: none
        MSG_CHAT,              // param1: message id, param2: queue position
    };

    enum EventType {
        EVENT_GP,
        EVENT_TEAM_GP,
        EVENT_BALLOON_BT,
        EVENT_COIN_BT,
    };

    u8 msgType;
    u16 param1;
    u8 param2;
};
size_assert(RKNetROOMPacket, 0x4);

union RKNetROOMPacketRaw {
    RKNetROOMPacketRaw(u32 data) : raw(data) {}

    RKNetROOMPacket packet;
    u32 raw;
};

#pragma pack(pop)
