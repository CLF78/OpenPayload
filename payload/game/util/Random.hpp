#include <common/Common.hpp>

class Random {
public:
    Random();

    virtual ~Random();

    u32 nextU32(u32 range);

    u64 x;
    u64 seed;
};
size_assert(Random, 0x18);
