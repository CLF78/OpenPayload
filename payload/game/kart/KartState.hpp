#include <common/Common.hpp>
#include <game/kart/KartObjectProxy.hpp>
#include <revolution/mtx.h>

class KartState {
public:

    enum Bitfield0 {
        ACCELERATE                   = BIT_FLAG(0),
        BRAKE                        = BIT_FLAG(1),
        DRIFT_INPUT                  = BIT_FLAG(2),
        DRIFT_MANUAL                 = BIT_FLAG(3),
        BEFORE_RESPAWN               = BIT_FLAG(4),
        WALL_3_COLLISION             = BIT_FLAG(5),
        WALL_COLLISION               = BIT_FLAG(6),
        HOP_START                    = BIT_FLAG(7),
        ACCELERATE_START             = BIT_FLAG(8),
        GROUND_START                 = BIT_FLAG(9),
        VEHICLE_BODY_FLOOR_COLLISION = BIT_FLAG(10),
        ANY_WHEEL_COLLISION          = BIT_FLAG(11),
        ALL_WHEELS_COLLISION         = BIT_FLAG(12),
        STICK_LEFT                   = BIT_FLAG(13),
        AIRTIME_OVER_20              = BIT_FLAG(15),
        STICKY_ROAD                  = BIT_FLAG(16),
        GROUND                       = BIT_FLAG(18),
        HOP                          = BIT_FLAG(19),
        BOOST                        = BIT_FLAG(20),
        AIR_START                    = BIT_FLAG(23),
        STICK_RIGHT                  = BIT_FLAG(24),
        SOMETHING_EXPLOSION          = BIT_FLAG(25),
        MUSHROOM_BOOST               = BIT_FLAG(26),
        SLIPDRIFT_CHARGE             = BIT_FLAG(27),
        DRIFT_AUTO                   = BIT_FLAG(28),
        WHEELIE                      = BIT_FLAG(29),
        JUMP_PAD                     = BIT_FLAG(30),
        RAMP_BOOST                   = BIT_FLAG(31),
    };

    enum Bitfield1 {
        HIT_ITEM_OR_OBJ             = BIT_FLAG(0),
        TRIGGER_RESPAWN             = BIT_FLAG(1),
        CANNON_START                = BIT_FLAG(3),
        IN_CANNON                   = BIT_FLAG(4),
        TRICK_START                 = BIT_FLAG(5),
        IN_A_TRICK                  = BIT_FLAG(6),
        BOOST_OFFROAD_INVINCIBILITY = BIT_FLAG(7),
        ZIPPER_COLLISION            = BIT_FLAG(9),
        OVER_ZIPPER                 = BIT_FLAG(10),
        MUSHROOM_COLLISION          = BIT_FLAG(11),
        ZIPPER_BOOST                = BIT_FLAG(13),
        ZIPPER_TRICK                = BIT_FLAG(15),
        MT_BOOST                    = BIT_FLAG(20),
        HAS_TRICK_ROT               = BIT_FLAG(22),
        TRICKABLE                   = BIT_FLAG(30),
        IN_A_STAR                   = BIT_FLAG(31),
    };

    enum Bitfield2 {
        CHARGING_A_SLIPSTREAM  = BIT_FLAG(0),
        IN_A_SLIPSTREAM        = BIT_FLAG(1),
        SOMETHING_WHEELIE_BUMP = BIT_FLAG(2),
        WHEELIE_ROT            = BIT_FLAG(4),
        UNK_20                 = BIT_FLAG(5),
        SHOCKED                = BIT_FLAG(7),
        UNK_100                = BIT_FLAG(8),
        IN_RESPAWN             = BIT_FLAG(13),
        AFTER_RESPAWN          = BIT_FLAG(14),
        IN_A_MEGA              = BIT_FLAG(15),
        CRUSHED                = BIT_FLAG(16),
        HAS_STOPPED_B2         = BIT_FLAG(18),
        HAS_VANISHED           = BIT_FLAG(19),
        HAS_JUMP_PAD_DIR       = BIT_FLAG(22),
        IN_A_BULLET            = BIT_FLAG(27),
        INK_APPLIED            = BIT_FLAG(28),
        IN_A_TC                = BIT_FLAG(29),
    };

    enum Bitfield3 {
        SOMETHING_WALL_COLLISION = BIT_FLAG(3),
        HWG                      = BIT_FLAG(5),
        UNK_40                   = BIT_FLAG(6),
        CHARGE_START_BOOST       = BIT_FLAG(8),
    };

    enum Bitfield4 {
        CPU                   = BIT_FLAG(0),
        LOCAL                 = BIT_FLAG(1),
        ONLINE_LOCAL          = BIT_FLAG(2),
        ONLINE_REMOTE         = BIT_FLAG(3),
        AUTOMATIC_DRIFT       = BIT_FLAG(4),
        GHOST                 = BIT_FLAG(6),
        BATTLE_RESPAWN        = BIT_FLAG(7),
        HAS_STOPPED_B4        = BIT_FLAG(12),
        BEFORE_BATTLE_RESPAWN = BIT_FLAG(17),
    };

    virtual ~KartState();

    void handleStartBoost();

    u32 bitfield0;
    u32 bitfield1;
    u32 bitfield2;
    u32 bitfield3;
    u32 bitfield4;

    KartObjectProxy* mpProxy;

    u32 airtime;
    u32 _20;

    float _24;
    VEC3 _28;
    VEC3 _34;
    VEC3 _40;
    VEC3 _4C;

    float _58;
    float _5C;
    VEC3 _60;

    s32 hwgTimer;
    s32 _70;

    s32 boostRampType;
    u32 jumpPadType;
    float _7C;

    u32 cnptId;
    s16 _84;
    s16 _86;

    float stickX;
    float stickY;

    s32 oobWipeState;
    s16 oobWipeFrame;
    // 2 bytes padding

    float _98;
    float startBoostCharge;
    s32 startBoostIdx;
    s16 _A4;

    s16 trickableTimer;

    VEC3 _A8;
    VEC3 _B4;
};
