#include <common/Common.hpp>
#include <game/system/RaceMode.hpp>

class RaceModeOnlineVs : public RaceMode {
public:
    bool tryEndRaceAfterLeaderFinish();
    void endLocalRaceWithReason(int reason);

    u8 unk[0x174-0x8];
};
size_assert(RaceModeOnlineVs, 0x174);
