#include <common/Common.hpp>
#include <game/net/WifiDisconnectInfo.hpp>

class GlobalContext {
public:

    enum VehicleRestriction {
        VEHICLES_KARTS,
        VEHICLES_BIKES,
        VEHICLES_ALL,
    };

    u8 unk[0x60];

    u32 currentRace;
    u32 raceCount;
    u32 redTeamVictories;
    u32 blueTeamVictories;
    int lastVictoryTeam;
    u32 vehicleRestriction;

    // Modified
    u16* trackOrder;
    u32 nextTracks[31]; // free for use

    int vsRaceLimit;

    // Modified
    u16* arenaOrder;
    u32 nextArenas[9]; // free for use

    u32 humanPlayerCount;
    u32 _128;

    int playerCharacters[4];
    int playerVehicles[4];

    s32 lastCourse;
    s32 lastStage;
    u8 unk2[0x4D0 - 0x154];

    int demoCameraMode;
    int demoType;
    int demoBattleType;
    u32 _4DC;
    int demoTrack;
    int demoArena;

    u8 unk3[0x500-0x4E8];

    WifiDisconnectInfo disconnectInfo;
    u8 unk4[0x510-0x508];
};
size_assert(GlobalContext, 0x510);
