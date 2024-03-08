#include <common/Common.hpp>
#include <game/host_system/ParameterFile.hpp>
#include <game/system/Competition.hpp>
#include <game/system/GhostFile.hpp>
#include <game/system/Mii.hpp>
#include <game/system/Rating.hpp>

class RaceConfigEx {
public:
    virtual ~RaceConfigEx();
};
size_assert(RaceConfigEx, 0x4);

class RaceConfig : public RaceConfigEx, public ParameterFile {
public:

    class Player {
    public:
        enum Type {
            TYPE_LOCAL,
            TYPE_CPU,
            TYPE_UNUSED,
            TYPE_GHOST,
            TYPE_ONLINE,
            TYPE_NONE,
        };

        enum Team {
            TEAM_RED,
            TEAM_BLUE,
            TEAM_NONE,
        };

        virtual ~Player();

        int computeGPRank();

        u8 _4;
        s8 localPlayerNum;
        s8 playerInputIdx;
        u32 vehicleId;
        u32 characterId;
        u32 playerType;
        Mii mii;
        u32 team;
        s32 controllerId;
        u32 _D4;
        u16 previousScore;
        u16 gpScore;
        u16 _DC;
        s16 gpRankScore;
        u8 gpRank;
        u8 prevFinishPos;
        u8 finishPos;
        Rating rating;
        s8 _EC;
    };
    size_assert(Player, 0xF0);

    struct Settings {

        enum EngineClass {
            CC_50,
            CC_100,
            CC_150,
            CC_COUNT,
        };

        enum GameMode {
            GAMEMODE_GP,
            GAMEMODE_VS,
            GAMEMODE_TT,
            GAMEMODE_BT,
            GAMEMODE_MR,
            GAMEMODE_GHOST_RACE,
            GAMEMODE_UNK_6,
            GAMEMODE_PRIVATE_VS,
            GAMEMODE_PUBLIC_VS,
            GAMEMODE_PUBLIC_BT,
            GAMEMODE_PRIVATE_BT,
            GAMEMODE_AWARDS,
            GAMEMODE_CREDITS,
        };

        enum CameraMode {
            CAMERA_MODE_GAMEPLAY_NO_INTRO,
            CAMERA_MODE_REPLAY,
            CAMERA_MODE_TITLE_1P,
            CAMERA_MODE_TITLE_2P,
            CAMERA_MODE_TITLE_4P,
            CAMERA_MODE_GAMEPLAY_INTRO,
            CAMERA_MODE_LIVE_VIEW,
            CAMERA_MODE_GP_WIN,
            CAMERA_MODE_SOLO_VS_WIN,
            CAMERA_MODE_TEAM_VS_WIN,
            CAMERA_MODE_BT_WIN,
            CAMERA_MODE_UNK_B,
            CAMERA_MODE_LOSS,
        };

        enum BattleType {
            BATTLE_BALLOON,
            BATTLE_COIN,
        };

        enum CPUMode {
            CPU_EASY,
            CPU_NORMAL,
            CPU_HARD,
            CPU_NONE,
        };

        enum ModeFlags {
            FLAG_MIRROR      = BIT_FLAG(0),
            FLAG_TEAMS       = BIT_FLAG(1),
            FLAG_COMPETITION = BIT_FLAG(2),
        };

        enum ItemMode {
            ITEMS_BALANCED,
            ITEMS_FRANTIC,
            ITEMS_STRATEGIC,
            ITEMS_NONE,
        };

        bool isBattle() const {
            switch (gameMode) {
                case GAMEMODE_BT:
                case GAMEMODE_PUBLIC_BT:
                case GAMEMODE_PRIVATE_BT:
                    return true;
                default:
                    return false;
            }
        }

        bool isOnline() const {
            switch (gameMode) {
                case GAMEMODE_PRIVATE_VS:
                case GAMEMODE_PUBLIC_VS:
                case GAMEMODE_PUBLIC_BT:
                case GAMEMODE_PRIVATE_BT:
                    return true;
                default:
                    return false;
            }
        }

        u32 courseId;
        u32 engineClass;
        u32 gameMode;
        u32 cameraMode;
        u32 battleType;
        u32 cpuMode;
        u32 itemMode;
        s8 hudPlayerIds[4];
        u32 cupId;
        u8 raceNumber;
        u8 lapCount;
        u32 modeFlags;
        u32 seed1;
        u32 seed2;
    };
    size_assert(Settings, 0x34);

    class Scenario {
    public:
        virtual ~Scenario();

        u8 playerCount;
        u8 hudCount;
        u8 localPlayerCount;
        u8 hudCount2;
        Player players[12];
        Settings settings;
        CompetitionSettings competitionSettings;
        RawGhostFile* ghost;
    };
    size_assert(Scenario, 0xBF0);

    virtual ~RaceConfig();

    Scenario raceScenario;
    Scenario menuScenario;
    Scenario awardsScenario;
    RawGhostFile ghosts[2];

    static RaceConfig* instance;
};
size_assert(RaceConfig, 0x73F0);
