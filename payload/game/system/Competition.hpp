#include <common/Common.hpp>

struct CharacterVehicleChoice {
    s8 characterId;
    s8 vehicleId;
};
size_assert(CharacterVehicleChoice, 0x2);

struct CompetitionSettings {
    u16 missionFileId;
    u16 missionType;
    u8 courseId;
    u8 characterId;
    u8 vehicleId;
    u8 engineClass;
    u8 _8[0x24];

    u16 timeLimit;
    u8 _2E;
    u8 controllerRestriction;
    u32 scores[6];

    u16 cameraAngle;
    u16 minimapObject;
    u16 _4C;
    u16 _4E;
    u16 cannonFlag;
    u8 _52[6];
    u16 cpuCount;
    CharacterVehicleChoice cpuCombos[11];
};
size_assert(CompetitionSettings, 0x70);
