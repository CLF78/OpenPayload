#include <common/Common.hpp>

class RKNetPacketHolder {
public:
    void* buffer;
    u32 bufferSize;
    u32 currentPacketSize;
};
size_assert(RKNetPacketHolder, 0xC);

class RKNetRACEPacketHolder {
public:
    RKNetPacketHolder* header;
    RKNetPacketHolder* raceHeader1;
    RKNetPacketHolder* raceHeader2;
    RKNetPacketHolder* select;
    RKNetPacketHolder* racedata;
    RKNetPacketHolder* user;
    RKNetPacketHolder* item;
    RKNetPacketHolder* event;
};
size_assert(RKNetRACEPacketHolder, 0x20);
