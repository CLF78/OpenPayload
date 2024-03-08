#include <common/Common.h>
#include <gs/common/gsAvailable.h>
#include <gs/common/gsPlatformUtil.h>
#include <gs/common/gsSocketRevolution.h>
#include <gs/natneg/natneg.h>
#include <revolutionex/so/SOBasic.h>
#include <wiimmfi/Natify.hpp>

// Ported from GameSpy SDK
u32 NameToIp(const char* name) {

    SOHostEnt* hent = gethostbyname(name);
    if (!hent) return 0;
    return hent->addrList[0][0];
}

// Ported from GameSpy SDK
BOOL ResolveServers() {

    if (matchup1ip == 0)
        matchup1ip = NameToIp(Matchup1Hostname);

    if (matchup2ip == 0)
        matchup2ip = NameToIp(Matchup2Hostname);

    if (matchup3ip == 0)
        matchup3ip = NameToIp(Matchup3Hostname);

    if (matchup1ip == 0 || matchup2ip == 0 || matchup3ip == 0)
        return FALSE;

    return TRUE;
}

// Ported from GameSpy SDK
int NNStartNatDetection(NatDetectionResultsFunc resultscallback) {

    // Check if the backend is available
    if(__GSIACResult != GSIAC_AVAILABLE)
        return NN_SOCKET_ERROR;

    if (!ResolveServers())
        return NN_DNS_ERROR;

    activeNatify = TRUE;
    natifyCallback = resultscallback;
    natifyStartTime = current_time();

    // Assume these for now
    nat.ipRestricted = TRUE;
    nat.portRestricted = TRUE;

    // Create socket for external reach tests
    ertSock = socket(SO_PF_IPV4, SO_SOCK_UDP, SO_IPPROTO_UDP);

    // Create socket for determining how traffic is mapped
    mappingSock = socket(SO_PF_IPV4, SO_SOCK_UDP, SO_IPPROTO_UDP);

    // Send reachability packets
    DiscoverReachability(ertSock, matchup1ip, NATNEG_PORT, NN_PT_NN1);
    DiscoverReachability(ertSock, matchup1ip, NATNEG_PORT, NN_PT_NN2);
    DiscoverReachability(ertSock, matchup2ip, NATNEG_PORT, NN_PT_NN3);

    // Send mapping packets
    DiscoverMapping(mappingSock, matchup1ip, NATNEG_PORT, NN_PT_NN1, NATIFY_MAP_1A);
    DiscoverMapping(mappingSock, matchup1ip, NATNEG_PORT, NN_PT_NN1, NATIFY_MAP_1B);
    DiscoverMapping(mappingSock, matchup2ip, NATNEG_PORT, NN_PT_NN2, NATIFY_MAP_2);
    DiscoverMapping(mappingSock, matchup3ip, NATNEG_PORT, NN_PT_NN3, NATIFY_MAP_3);

    return NN_NO_ERROR;
}

/////////////////
// Fast NATNEG //
/////////////////

// NegotiateThink() patch
// Reduce PING retry time from 700 to 80
// Credits: Wiimmfi
kmWrite16(0x8011B47A, 80);

// NegotiateThink() patch
// Do not wait the retry time in case of successful NATNEG
// Credits: Wiimmfi
kmWrite32(0x8011B4B0, 0x60000000);

// ProcessPingPacket() patch
// Do not wait the idle time after a successful NATNEG
// Credits: WiiLink24
kmWrite16(0x8011BC3A, 0);

/////////////////////////
// NATify Improvements //
/////////////////////////

// SendInitPackets() patch
// Modify INIT packets to send the NATify data
// Credits: Wiimmfi
kmCallDefCpp(0x8011AB28, int, u8* buffer) {
    return Wiimmfi::Natify::CopyData(buffer);
}

// SendInitPackets() patch
// Replace INIT message type
// Credits: Wiimmfi
kmWrite32(0x8011AB2C, 0x3BC00000 | WIIMMFI_NATIFY);
kmWrite32(0x8011AB30, 0x9BC1004F);
