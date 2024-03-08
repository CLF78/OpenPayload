#include <common/Common.hpp>

struct RawSave {

    struct License {
        u8 data[0x8CC0];
    };
    size_assert(License, 0x8CC0);

    struct GlobalData {

        enum Settings {
            CONTROLLER_RUMBLE    = BIT_FLAG(0),
            FLAG_REGION_DISPLAY  = BIT_FLAG(1),
            UNK_4                = BIT_FLAG(2),
            MESSAGE_SERVICE      = BIT_FLAG(3),
            DATA_SHARING         = BIT_FLAG(4),
            MII_DISPLAY          = BIT_FLAG(5),
            DEFAULT_VALUE        = MII_DISPLAY | UNK_4 | FLAG_REGION_DISPLAY | CONTROLLER_RUMBLE,

            // Custom fields below
            WIIMMFI_DATA_SHARING = BIT_FLAG(7),
        };

        u32 magic;
        u32 settings;
        u8 unk[0x37FA];
        u16 regionId;
    };
    size_assert(GlobalData, 0x3804);

    struct UnkBlock {
        u8 data[0x14F0];
    };
    size_assert(UnkBlock, 0x14F0);

    u32 magic;
    u32 version;
    License licenses[4];
    GlobalData globalData;
    UnkBlock unkBlock;
    u32 crc32;
};
size_assert(RawSave, 0x28000);
