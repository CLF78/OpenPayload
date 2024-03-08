#include <common/Common.hpp>

enum RKNetStatus {
    STATUS_INACTIVE         = 0,
    STATUS_WAITING          = 2,
    STATUS_ROOM_HOST        = 3,
    STATUS_ROOM_GUEST       = 4,
    STATUS_PUBLIC_VS        = 5,
    STATUS_PUBLIC_BT        = 8,
    STATUS_PRIVATE_VS_HOST  = 11,
    STATUS_PRIVATE_VS_GUEST = 12,
    STATUS_PRIVATE_BT_HOST  = 13,
    STATUS_PRIVATE_BT_GUEST = 14,
};

struct RKNetStatusData {
    u32 groupId;
    u8 searchRegion; // 0xFF for Worldwides
    u8 status; // see enum above
    u8 playerCount;
    u8 raceNumber;
};
