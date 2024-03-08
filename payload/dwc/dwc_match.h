#include <common/Common.h>
#include <dwc/dwc_account.h>
#include <dwc/dwc_error.h>
#include <dwc/dwc_node.h>
#include <gs/gp/gpi.h>
#include <gs/gt2/gt2Callback.h>
#include <gs/gt2/gt2Main.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DWC_MATCH_CMD_GET_ACTUAL_SIZE(size) ((size) * 4)
#define DWC_MATCH_CMD_GET_SIZE(size) ((size) / 4)

typedef void (*DWCMatchedCallback)(DWCError error, int cancel, int self, int isServer, int index, void* param);
typedef void (*DWCNewClientCallback)(int friendIndex, void* param);
typedef int (*DWCEvalCallback)(int serverBrowserCount, void* param);
typedef int (*DWCConnectAttemptCallback)(u8* userData, void* param);

typedef enum {
    DWC_MATCH_STATE_INIT,
    DWC_MATCH_STATE_CL_WAITING,
    DWC_MATCH_STATE_CL_SEARCH_HOST,
    DWC_MATCH_STATE_CL_WAIT_RESV,
    DWC_MATCH_STATE_CL_NN,
    DWC_MATCH_STATE_CL_GT2,
    DWC_MATCH_STATE_CL_CANCEL_SYN,
    DWC_MATCH_STATE_CL_SYN,
    DWC_MATCH_STATE_CL_SVDOWN_1,
    DWC_MATCH_STATE_CL_SVDOWN_2,
    DWC_MATCH_STATE_CL_SVDOWN_3,
    DWC_MATCH_STATE_CL_SEARCH_GROUPID_HOST,
    DWC_MATCH_STATE_SV_WAITING,
    DWC_MATCH_STATE_SV_OWN_NN,
    DWC_MATCH_STATE_SV_OWN_GT2,
    DWC_MATCH_STATE_SV_CANCEL_SYN,
    DWC_MATCH_STATE_SV_CANCEL_SYN_WAIT,
    DWC_MATCH_STATE_SV_SYN,
    DWC_MATCH_STATE_SV_SYN_WAIT,
    DWC_MATCH_STATE_WAIT_CLOSE,
    DWC_MATCH_STATE_SEARCH_OWN,
    DWC_MATCH_STATE_COUNT,
} DWCMatchState;

typedef enum {
    DWC_MATCH_CMD_RESV            = 0x1,
    DWC_MATCH_CMD_RESV_OK         = 0x2,
    DWC_MATCH_CMD_RESV_DENY       = 0x3,
    DWC_MATCH_CMD_RESV_WAIT       = 0x4,
    DWC_MATCH_CMD_RESV_CANCEL     = 0x5,
    DWC_MATCH_CMD_TELL_ADDR       = 0x6,
    DWC_MATCH_CMD_NEW_PID_AID     = 0x7,
    DWC_MATCH_CMD_LINK_CLOSE_REQ  = 0x8,
    DWC_MATCH_CMD_LINK_CLOSE_SUC  = 0x9,
    DWC_MATCH_CMD_CLOSE_LINK      = 0xA,
    DWC_MATCH_CMD_RESV_PRIOR      = 0xB,
    DWC_MATCH_CMD_CANCEL          = 0xC,
    DWC_MATCH_CMD_CANCEL_SYN      = 0xD,
    DWC_MATCH_CMD_CANCEL_SYN_ACK  = 0xE,
    DWC_MATCH_CMD_CANCEL_ACK      = 0xF,
    DWC_MATCH_CMD_SC_CLOSE_CL     = 0x10,
    DWC_MATCH_CMD_POLL_TIMEOUT    = 0x11,
    DWC_MATCH_CMD_POLL_TO_ACK     = 0x12,
    DWC_MATCH_CMD_SC_CONN_BLOCK   = 0x13,
    DWC_MATCH_CMD_SVDOWN_QUERY    = 0x52,
    DWC_MATCH_CMD_SVDOWN_ACK      = 0x53,
    DWC_MATCH_CMD_SVDOWN_NAK      = 0x54,
    DWC_MATCH_CMD_SVDOWN_KEEP     = 0x55,
    DWC_MATCH_CMD_SB_RETRY_SEARCH = 0x72,
    DWC_MATCH_CMD_SUSPEND_CTRL    = 0x82,
    DWC_MATCH_CMD_USED_SLOTS      = 0x83,

    // Custom commands from here onwards
    DWC_MATCH_CMD_CTGP_RULE_D0    = 0xD0,
    DWC_MATCH_CMD_CTGP_RULE_D1    = 0xD1,
    DWC_MATCH_CMD_CTGP_RULE_D2    = 0xD2,
    DWC_MATCH_CMD_CTGP_RULE_D3    = 0xD3,

    DWC_MATCH_DNS_EXPLOIT_D4      = 0xD4,
    DWC_MATCH_DNS_EXPLOIT_D5      = 0xD5,

    DWC_MATCH_CMD_CONN_FAIL_MTX   = 0xDC,
    DWC_MATCH_CMD_CONN_MTX        = 0xDD,
} DWCMatchCommandType;

typedef enum {
    DWC_MATCH_SYN_CMD_SYN = 0x1,
} DWCSynMatchCommandType;

typedef struct {
    u32 pid; // endian-swapped
    u32 aid; // endian-swapped
} DWCMatchCommandNewPidAid;

typedef struct {
    u8 command;
    u8 count;
    u16 port;
    u32 ip;
    u32 data[32];
    int profileId;
    int len;
    s64 sendTime;
} DWCMatchCommandControl;

typedef struct {
    u8 isQr2;
    u8 retryCount;
    u16 port;
    u32 ip;
    int cookie;
} DWCNNInfo;

typedef struct {
    GPConnection gpConnection;
    GT2Socket* gt2Socket;
    GT2Callbacks* gt2Callbacks;
    u8 gt2ConnectCount;
    u8 connectedOnceBefore;
    // 2 bytes padding

    void* qr2; // TODO header
    u8 qr2MatchType;
    u8 qr2MatchTypeExt;
    u8 hostState;
    u8 qr2NumEntry;
    u8 qr2IsReserved;
    u8 pad;
    // 2 bytes padding

    u32 suspendMatchBitmap;
    s64 suspendRequestTick;
    int suspendMatch;
    u8 suspend;
    u8 suspendServerResponse;
    u8 pad2;
    // 1 byte padding

    DWCNodeInfoList nodeInfoList;
    DWCNodeInfo tempNewNodeInfo;
    DWCNodeInfo tempNewClientInfo;
    int inMeshMaking;
    DWCMatchState lastStateBeforeStopMeshMaking;
    DWCNodeInfo tempNodeInfoBeforeStopMeshMaking;

    u16 qr2Port;
    // 2 bytes padding
    u32 qr2IP;
    int qr2Reservation;

    void* serverBrowser; // TODO header
    int serverBrowserUpdateFlag;
    // 4 bytes padding
    s64 serverBrowserUpdateTick;
    s64 serverBrowserUpdateRequestTick;

    u8 natnegRecvCount;
    u8 natnegFailureCount;
    u16 natnegCookieRand;
    int natnegLastCookie;
    s64 natnegFailedTime;
    s64 natnegFinishTime;
    DWCNNInfo natnegInfo;

    DWCMatchState state;
    u8 resvWaitCount;
    u8 closeState;
    u8 cancelState;
    u8 scResvRetryCount;
    u8 synResendCount;
    u8 cancelSynResendCount;
    u8 clWaitTimeoutCount;
    u8 _727[3]; // padding

    u16 baseLatency;
    u16 cancelBaseLatency;
    // 2 bytes padding
    u32 natnegResvCheckValue;

    int cmdResendFlag;
    s64 cmdResendTick;
    u32 cmdTimeoutTime;
    // 4 bytes padding
    s64 cmdTimeoutStartTick;

    u32 synAckBit;
    u32 cancelSynAckBit;
    s64 lastSynSent;
    s64 lastCancelSynSent;
    s64 closedTime;
    s64 clWaitTime;

    int profileId;
    u32 reqProfileId;
    int cbEventPid;

    const char* gameName;
    const char* secretKey;

    const DWCFriendData* friendList;
    int friendListLength;
    u8 friendIdxList[64];
    int friendIdxListLength;

    DWCMatchCommandControl cmdCnt;
    DWCMatchedCallback matchedCallback;
    void* matchedCallbackParam;
    DWCNewClientCallback newClientCallback;
    void* newClientCallbackParam;
    DWCEvalCallback evalCallback;
    void* evalCallbackParam;

    u32 serverDownBuff;
    u32 serverDownBase;
    u32 groupId;
    u8 searchGroupIdRetryHostCount;
    u8 connectGroupId;
    u8 serverDownQueryCount;
    u8 serverDownNakCount;
    s64 serverPollingTime;

    u8 _8A0;
    u8 _8A1;
    // 2 bytes padding

    DWCConnectAttemptCallback connectAttemptCallback;
    u8 connUserData[4];
    void* connectAttemptParam;

    u32 serverPollingUID;
    // 4 bytes padding
    s64 suspendWaitTime;
} DWCMatchControl;

void DWCi_GT2ConnectAttemptCallback(GT2Socket socket, GT2Connection conn, u32 ip, u16 port, int latency,
                                    const char* msg, int msgLen);
void DWCi_GT2ConnectedCallback(GT2Connection conn, GT2Result result, const char* msg, int msgLen);

BOOL DWCi_ProcessRecvMatchCommand(u8 cmd, int profileId, u32 publicIp, u16 publicPort, void* cmdData, int dataLen);
int DWCi_SendMatchCommand(u8 cmd, int profileId, u32 publicIp, u16 publicPort, void* cmdData, int dataLen);
void DWCi_SendMatchSynPacket(u8 aid, u16 type);
void DWCi_SetMatchStatus(DWCMatchState status);

s64 DWCi_GetNextMeshMakeTryTick();
BOOL DWCi_StopMeshMaking();

extern DWCMatchControl* stpMatchCnt;
extern s64 sMatchStateTick;

#ifdef __cplusplus
}
#endif
