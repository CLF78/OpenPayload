#include <common/Common.h>
#include <gs/natneg/natify.h>

#ifdef __cplusplus
extern "C" {
#endif
#pragma pack(push, 1)

#define NATNEG_MAGIC_LEN 6
#define NATNEG_PORT 27901
#define NATNEG_PROTOCOL_VERSION 3

typedef enum {
    NN_NO_ERROR,
    NN_ALLOC_ERROR,
    NN_SOCKET_ERROR,
    NN_DNS_ERROR,
} NATNEGError;

typedef enum {
    NN_STATE_INIT_SENT,
    NN_STATE_INIT_ACK,
    NN_STATE_INIT_CONNECT_PING,
    NN_STATE_FINISHED,
    NN_STATE_CANCELED,
    NN_STATE_REPORT_SENT,
    NN_STATE_REPORT_ACK,
} NATNEGState;

typedef enum {
    NN_RESULT_SUCCESS,
    NN_RESULT_DEADBEAT_PARTNER,
    NN_RESULT_INIT_TIMEOUT,
    NN_RESULT_PING_TIMEOUT,
    NN_RESULT_UNK_ERROR,
    NN_RESULT_NONE,
} NATNEGResult;

typedef enum {
    NN_PT_GP,
    NN_PT_NN1,
    NN_PT_NN2,
    NN_PT_NN3,
} NATNEGPortType;

typedef enum {
    NN_INIT,
    NN_INITACK,
    NN_ERTTEST,
    NN_ERTACK,
    NN_STATEUPDATE,
    NN_CONNECT,
    NN_CONNECT_ACK,
    NN_CONNECT_PING,
    NN_BACKUP_TEST,
    NN_BACKUP_ACK,
    NN_ADDRESS_CHECK,
    NN_ADDRESS_REPLY,
    NN_NATIFY_REQUEST,
    NN_REPORT,
    NN_REPORT_ACK,

    // Custom commands from here onwards
    WIIMMFI_NATIFY = 0x80,
} NATNEGCommand;

typedef struct {
    u8 porttype;
    u8 clientindex;
    u8 usegameport;
    u32 localip;
    u16 localport;
} InitPacket;

typedef struct {
    u8 portType;
    u8 clientindex;
    u8 negResult;
    int natType;
    int natMappingScheme;
    char gamename[50];
} ReportPacket;

typedef struct {
    u32 remoteIP;
    u16 remotePort;
    u8 gotData;
    u8 finished;
} ConnectPacket;

typedef struct {
    u8 magic[NATNEG_MAGIC_LEN];
    u8 version;
    u8 packetType;
    int cookie;

    union {
        InitPacket init;
        ConnectPacket connect;
        ReportPacket report;
    } data;

} NATNEGPacket;

typedef void (*NegotiateProgressFunc)(int state, void* userData);
typedef void (*NegotiateCompletedFunc)(int result, int gamesocket, SOSockAddrIn* remoteAddr, void* userData);
typedef void (*NatDetectionResultsFunc)(BOOL success, NAT* nat);

typedef struct {
    int negotiateSock;
    int gameSock;
    int cookie;
    int clientindex;
    int state;
    int initAckRecv[4];
    int retryCount;
    int maxRetryCount;
    u32 retryTime;
    u32 guessedIP;
    u16 guessedPort;
    u8 gotRemoteData;
    u8 sendGotRemoteData;
    NegotiateProgressFunc progressCallback;
    NegotiateCompletedFunc completedCallback;
    void *userdata;
    int result;
    int connectedSocket;
    SOSockAddrIn remoteAddr;
} NATNegotiator;

void NegotiateThink(NATNegotiator* neg);
int NNStartNatDetection(NatDetectionResultsFunc resultscallback); // reimplemented

extern char Matchup1Hostname[], Matchup2Hostname[], Matchup3Hostname[];
extern u32 matchup1ip, matchup2ip, matchup3ip;
extern int mappingSock, ertSock;
extern BOOL activeNatify;
extern u32 natifyStartTime;
extern NatDetectionResultsFunc natifyCallback;
extern NAT nat;
extern u8 NNMagicData[NATNEG_MAGIC_LEN];

#pragma pack(pop)
#ifdef __cplusplus
}
#endif
