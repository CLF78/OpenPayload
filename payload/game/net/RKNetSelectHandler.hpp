#include <common/Common.hpp>
#include <game/net/packet/RKNetSelectPacket.hpp>

class RKNetSELECTHandler {
public:
    enum Mode {
        MODE_NONE,
        MODE_PUBLIC_VS,
        MODE_PUBLIC_BATTLE,
        MODE_PRIVATE_VS,
        MODE_PRIVATE_BATTLE,
    };

    int mode;
    // 4 bytes padding

    RKNetSELECTPacket sendPacket;
    RKNetSELECTPacket recvPackets[12];
    u8 lastSentToAid;
    // 7 bytes padding

    s64 lastSentTime;
    s64 lastRecvTimes[12];
    s64 lastRecvDelays[12];
    u32 timelyRecvPacketCounts[12];

    // Bitfields follow
    u32 aidsWithNewSelect;
    u32 aidsWithNewRH1;
    u32 aidsWithNewRaceSettings;
    u32 aidsWithVoteData;
    u32 aidsThatHaveVoted;
    // 4 bytes padding

    static RKNetSELECTHandler* instance;
};
size_assert(RKNetSELECTHandler, 0x3F8);
