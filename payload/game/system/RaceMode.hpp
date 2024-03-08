#include <common/Common.hpp>
#include <game/system/RaceManager.hpp>

class RaceMode {
public:
    virtual ~RaceMode();
    virtual bool canEndRace();
    virtual void endRace();
    virtual void calc();
    virtual void calcPosition();
    virtual void getJugemPoint();
    virtual void init();
    virtual void vf_20();
    virtual void tryEndRace();
    virtual void vf_28();

    RaceManager* manager;
};
size_assert(RaceMode, 0x8);
