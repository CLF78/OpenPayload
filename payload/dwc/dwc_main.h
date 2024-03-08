#include <common/Common.h>
#include <dwc/dwc_match.h>
#include <gs/gt2/gt2Main.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    GT2Socket socket;
    GT2Callbacks callbacks;
    u8 unk[0x88 - 0x14];
    DWCMatchedCallback userMatchedCallback;
    void* userMatchedCallbackParam;
    u8 unk2[0x360 - 0x90];
    DWCMatchControl matchControl;
} DWCControl; // TODO finish header

typedef struct {
    u8 index;
    u8 aid;
    u16 pad;
    u32 profileId;
} DWCConnectionInfo;

BOOL DWC_IsServerMyself();
int DWC_CloseAllConnectionsHard();
int DWC_CloseConnectionHard(u8 aid);

int DWCi_GT2GetConnectionListIdx();
GT2Connection* DWCi_GetGT2ConnectionByIdx(int idx);
GT2Connection DWCi_GetGT2Connection(u8 aid);
DWCConnectionInfo* DWCi_GetConnectionInfoByIdx(int idx);

u8 DWC_GetMyAID();
u8 DWC_GetServerAID();
u32 DWC_GetAIDBitmap();

extern DWCControl* stpDwcCnt;

#ifdef __cplusplus
}
#endif
