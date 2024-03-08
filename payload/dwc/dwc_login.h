#include <common/Common.h>
#include <dwc/dwc_account.h>
#include <dwc/dwc_error.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DWC_LOGIN_STATE_INIT,
    DWC_LOGIN_STATE_REMOTE_AUTH,
    DWC_LOGIN_STATE_CONNECTING,
    DWC_LOGIN_STATE_GPGETINFO,
    DWC_LOGIN_STATE_GPSETINFO,
    DWC_LOGIN_STATE_CONNECTED,
    DWC_LOGIN_STATE_COUNT,
} DWCLoginState;

typedef void (*DWCLoginCallback)(DWCError error, int profileID, void* param);

typedef struct {
    void* gpConnection;
    DWCLoginState state;
    int productID;
    u32 gamecode;
    u16* playerName;
    DWCLoginCallback callback;
    void* param;
    DWCUserData* userdata;
    void* bmwork;
    void* http;
    u64 startTick;
    u32 connectFlag;
    u64 connectTick;
    DWCLoginId tempLoginId;
    char authToken[256];
    char partnerChallenge[256];
    char username[21];
    u8 unk2[7];
} DWCLoginControl;

extern DWCLoginControl* stpLoginCnt;

u64 DWCi_Auth_GetConsoleUserId();

#ifdef __cplusplus
}
#endif
