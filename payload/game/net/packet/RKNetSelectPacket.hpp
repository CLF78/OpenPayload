#include <common/Common.hpp>

struct RKNetSELECTPlayer {
    u16 prevRaceRank;
    u16 sumPoints;
    u8 character;
    u8 vehicle;
    u8 courseVote;
    u8 starRank;
};
size_assert(RKNetSELECTPlayer, 0x8);

struct RKNetSELECTPacket {
    s64 timeSender;
    s64 timeReceived;
    RKNetSELECTPlayer playerData[2];
    u32 selectId;

    union {
        struct {
            u8 battleType;
            u32 teams : 24; // 0 = ??, 1 = red team, 2 = ??, 3 = ??
        };

        u32 raw;
    } battleTeamData;

    union {
        u8 playerIds[12];
        u32 raw[3];
    } playerIdToAid;

    u8 winningCourse;
    u8 phase; // 0 = prepare, 1 = voting, 2 = lottery
    u8 winningVoterAid;
    u8 engineClass;
};
size_assert(RKNetSELECTPacket, 0x38);
