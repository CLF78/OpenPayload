#include <common/Common.hpp>
#include <game/system/Timer.hpp>
#include <game/system/TimerManager.hpp>
#include <game/util/Random.hpp>

class RaceMode;

class RaceManager {
public:

    enum RaceStage {
        STAGE_INTRO,
        STAGE_COUNTDOWN,
        STAGE_RACE,
        STAGE_FINISH,
        STAGE_FINISH_ALL,
    };

    class Player {
    public:
        virtual ~Player();

        u8 unk[0x0A - 0x04];
        u16 checkpointId;

        u8 unk2[0x26 - 0x0C];
        u8 maxLap;

        u8 unk3[0x40 - 0x27];
        Timer* finishTime;

        u8 unk4[0x54 - 0x44];
    };
    size_assert(Player, 0x54);

    virtual ~RaceManager();

    Random* dynamicRandom;
    Random* staticRandom;
    Player** players;
    RaceMode* gameModeData;
    TimerManager* timerManager;
    u8 unk[0x20 - 0x18];

    u32 frameCounter;
    u8 unk2[0x28 - 0x24];

    u32 raceStage;
    u8 unk3[0x4C - 0x2C];

    static RaceManager* instance;
};
size_assert(RaceManager, 0x4C);
