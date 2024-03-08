#include <common/Common.h>

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum {
    DWC_REPORT_NONE            = BIT_FLAG(-1),
    DWC_REPORT_INFO            = BIT_FLAG(0),
    DWC_REPORT_ERROR           = BIT_FLAG(1),
    DWC_REPORT_DEBUG           = BIT_FLAG(2),
    DWC_REPORT_WARNING         = BIT_FLAG(3),
    DWC_REPORT_ACHECK          = BIT_FLAG(4),
    DWC_REPORT_LOGIN           = BIT_FLAG(5),
    DWC_REPORT_MATCH_NN        = BIT_FLAG(6),
    DWC_REPORT_MATCH_GT2       = BIT_FLAG(7),
    DWC_REPORT_TRANSPORT       = BIT_FLAG(8),
    DWC_REPORT_QR2_REQ         = BIT_FLAG(9),
    DWC_REPORT_SB_UPDATE       = BIT_FLAG(10),
    DWC_REPORT_SEND_INFO       = BIT_FLAG(15),
    DWC_REPORT_RECV_INFO       = BIT_FLAG(16),
    DWC_REPORT_UPDATE_SV       = BIT_FLAG(17),
    DWC_REPORT_CONNECTINET     = BIT_FLAG(18),
    DWC_REPORT_TEST            = BIT_FLAG(20),
    DWC_REPORT_AUTH            = BIT_FLAG(24),
    DWC_REPORT_AC              = BIT_FLAG(25),
    DWC_REPORT_BM              = BIT_FLAG(26),
    DWC_REPORT_UTIL            = BIT_FLAG(27),
    DWC_REPORT_OPTION_CF       = BIT_FLAG(28),
    DWC_REPORT_OPTION_CONNTEST = BIT_FLAG(29),
    DWC_REPORT_GAMESPY         = BIT_FLAG(31),
    DWC_REPORT_ALL             = 0xFFFFFFFF,
} DWCReportFlag;

void DWC_Printf(DWCReportFlag level, const char* fmt, ...);

#ifdef  __cplusplus
}
#endif
