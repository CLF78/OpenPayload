#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NATIFY_COOKIE 777

typedef enum {
    NATIFY_MAP_1A,
    NATIFY_MAP_2,
    NATIFY_MAP_3,
    NATIFY_MAP_1B,
    NATIFY_MAP_NUM,
} NatifyPacket;

typedef enum {
    NAT_PROMISCUITY_ALL,
    NAT_PROMISCUITY_NONE,
    NAT_PROMISCUITY_PORT,
    NAT_PROMISCUITY_IP,
    NAT_PROMISCUITY_UNKNOWN,
    NAT_PROMISCUITY_NUM,
} NATPromiscuity;

typedef enum {
    NAT_MAP_UNRECOGNIZED,
    NAT_MAP_PRIVATE_AS_PUBLIC,
    NAT_MAP_CONSISTENT_PORT,
    NAT_MAP_INCREMENTAL,
    NAT_MAP_MIXED,
    NAT_MAP_NUM,
} NATMapping;

typedef enum {
    NAT_TYPE_NONE,
    NAT_TYPE_FIREWALL_ONLY,
    NAT_TYPE_FULL_CONE,
    NAT_TYPE_RESTRICTED_CONE,
    NAT_TYPE_PORT_RESTRICTED_CONE,
    NAT_TYPE_SYMMETRIC,
    NAT_TYPE_UNKNOWN,
    NAT_TYPE_NUM,
} NATType;

typedef struct {
    u32 privateIp;
    u16 privatePort;
    u32 publicIp;
    u16 publicPort;
} AddressMapping;

typedef struct {
    char brand[32];
    char model[32];
    char firmware[64];
    BOOL ipRestricted;
    BOOL portRestricted;
    int promiscuity;
    int type;
    int mappingScheme;
    AddressMapping mappings[4];
    BOOL qr2Compatible;
} NAT;

BOOL DetermineNatType(NAT* nat);
int DiscoverReachability(int sock, unsigned int ip, unsigned short port, int portType); // reimplemented
int DiscoverMapping(int sock, unsigned int ip, unsigned short port, int portType, int id); // reimplemented

#ifdef __cplusplus
}
#endif
