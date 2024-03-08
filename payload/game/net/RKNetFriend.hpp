#include <common/Common.hpp>
#include <game/net/RKNetStatusData.hpp>

struct RKNetFriend {
    RKNetStatusData statusData;
    u8 status; // see DWCFriendStatus
    u8 _9; // bit flags, 4 if room open, 1 if online
    u8 _A;
    u8 _B;
};
size_assert(RKNetFriend, 0xC);
