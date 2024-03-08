#include <common/Common.hpp>

class RawMii {
public:
    u8 buffer[0x4C];
};
size_assert(RawMii, 0x4C);

struct unkStruct {
    u8 _0;
    u8 _1;
    u8 _2;
    u8 _3;
};
size_assert(unkStruct, 0x4);

class Mii {
public:
    virtual ~Mii();

    s32 _4;
    u8 _8;
    s8 _9;
    s32 _C;
    RawMii rawMii;
    s32 _5C;
    unkStruct _60;
    u32 _64;
    u32 _68[15];
    u8 _A4;
    u8 _A5;
    u8 _A6;
    u32 _A8;
    u8 _AC;
    u8 _AD;
    u8 _AE;
    u32 _B0;
    u32 _B4;
};
size_assert(Mii, 0xB8);
