#include <common/Common.h>
#include <gs/common/gsSocketRevolution.h>
#include <gs/natneg/natify.h>
#include <gs/natneg/natneg.h>
#include <revolutionex/so/SOBasic.h>

// Ported from GameSpy SDK
int DiscoverReachability(int sock, u32 ip, u16 port, int portType) {

    // Set up address
    SOSockAddrIn addr;
    addr.family = SO_PF_IPV4;
    addr.addr = ip;
    addr.port = port;

    // Set up packet
    NATNEGPacket p;
    memset(&p, 0, sizeof(p));
    memcpy(&p.magic, NNMagicData, sizeof(p.magic));
    p.version = NATNEG_PROTOCOL_VERSION;
    p.packetType = NN_NATIFY_REQUEST;
    p.cookie = NATIFY_COOKIE;
    p.data.init.porttype = portType;

    // Send it
    return sendto(sock, (const char*)&p, sizeof(p), 0, &addr, sizeof(addr));
}

// Ported from GameSpy SDK
int DiscoverMapping(int sock, u32 ip, u16 port, int portType, int id) {

    // Set up address
    SOSockAddrIn addr;
    addr.family = SO_PF_IPV4;
    addr.addr = ip;
    addr.port = port;

    // Set up packet
    NATNEGPacket p;
    memset(&p, 0, sizeof(p));
    memcpy(&p.magic, NNMagicData, sizeof(p.magic));
    p.version = NATNEG_PROTOCOL_VERSION;
    p.packetType = NN_ADDRESS_CHECK;
    p.cookie = id;
    p.data.init.porttype = portType;

    // Send it
    return sendto(sock, (const char*)&p, sizeof(p), 0, &addr, sizeof(addr));
}
