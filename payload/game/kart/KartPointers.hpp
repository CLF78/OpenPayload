#include <common/Common.hpp>

class KartSettings;
class KartState;
class KartBody;
class KartSuspension;
class KartTire;
class PlayerModel;
class KartSub;
class PlayerSound;
class KartMove;
class KartAction;
class KartCollide;
class KartEnemy;
class RacedataFactory;
class KartNetReceiver;
class BoxColUnit;
class KartBlink;
class KartKiller;
class VehiclePhysics;

class KartPointers {
public:

    KartSettings* kartSettings;
    KartState* kartState;
    KartBody* kartBody;
    KartSuspension** kartSuspensions;
    KartTire** kartTires;
    PlayerModel* playerModel;
    KartSub* kartSub;
    PlayerSound* playerSound;
    void* kartShadowMaybe;
    void* kartCamera;
    KartMove* kartMove;
    KartAction* kartAction;
    KartCollide* kartCollide;
    void* _34;
    KartEnemy* kartEnemy;
    RacedataFactory* racedataFactory;
    KartNetReceiver* kartNetReceiver;
    void* _44;
    void* _48;
    BoxColUnit* entity;
    void* _50;
    void* _54;
    KartBlink* kartBlink;
    void* _5C;
    KartKiller* kartKiller;
};
