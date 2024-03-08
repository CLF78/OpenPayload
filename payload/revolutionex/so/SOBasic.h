#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SO_PF_UNSPECIFIED = 0,
    SO_PF_IPV4 = 2,
    SO_PF_IPV6 = 23,
} SOProtocolFamily;

typedef enum {
    SO_SOCK_TCP = 1,
    SO_SOCK_UDP = 2,
} SOSocketType;

typedef enum {
    SO_IPPROTO_ICMP = 1,
    SO_IPPROTO_IGMP = 2,
    SO_IPPROTO_TCP = 6,
    SO_IPPROTO_UDP = 17,
} SOProtocolType;

typedef struct {
    u8 len;    // size of socket address structure
    u8 family; // address family
    u16 port;  // port number
    u32 addr;  // ip address
} SOSockAddrIn;

typedef struct {
    char* name;
    char** aliases;
    s16 addrType;
    s16 length;
    u32** addrList;
} SOHostEnt;

#ifdef __cplusplus
}
#endif
