#include <common/Common.hpp>
#include <revolution/os/OSMutex.h>

class RKNetMutex {
public:
    virtual ~RKNetMutex();
    OSMutex mutex;
};
size_assert(RKNetMutex, 0x1C);
