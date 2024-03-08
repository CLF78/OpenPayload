#include <common/Common.hpp>
#include <nw4r/math/types.hpp>
#include <nw4r/ut/utList.hpp>
#include <game/kart/KartPointers.hpp>

class KartObjectProxy {
public:
    KartPointers* pointers;
    nw4r::ut::Link linkList;

    u8 getPlayerIdx();
    VehiclePhysics* getVehiclePhysics();
    VEC3* getPlayerPosition();

    void setOobCamera();

    void FUN_80591050(int, bool, bool);
};
