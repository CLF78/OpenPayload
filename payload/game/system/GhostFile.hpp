#include <common/Common.hpp>
#include <game/system/Mii.hpp>

#pragma pack(push, 1)
struct RawGhostFile {

    union {
        u8 buffer[0x2800];

        struct {
            u32 magic;

            u32 raceMinutes : 7;
            u32 raceSeconds : 7;
            u32 raceMilliseconds : 10;
            u32 courseId : 6;
            u32 _pad0 : 2;

            u32 vehicleId : 6;
            u32 characterId : 6;
            u32 year : 7;
            u32 month : 4;
            u32 day : 5;
            u32 controllerId : 4;

            u16 _pad1 : 4;
            bool isCompressed : 1;
            u16 _pad2 : 2;
            u16 type : 7;
            u16 driftType : 1;
            u16 _pad3 : 1;

            u16 inputsSize;
            u8 lapCount;

            struct {
                u32 minutes : 7;
                u32 seconds : 7;
                u32 milliseconds : 10;
            } lapTimes[5];

            wchar_t userData[10];
            u8 countryCode;
            u8 stateCode;
            u16 locationCode;
            u32 _38;
            RawMii mii;
        };
    };
};
size_assert(RawGhostFile, 0x2800);

#pragma pack(pop)
