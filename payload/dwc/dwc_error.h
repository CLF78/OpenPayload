#include <common/Common.h>
#include <gs/gp/gp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DWC_ERROR_NONE,
    DWC_ERROR_DS_MEMORY_ANY,
    DWC_ERROR_AUTH_ANY,
    DWC_ERROR_AUTH_OUT_OF_SERVICE,
    DWC_ERROR_AUTH_STOP_SERVICE,
    DWC_ERROR_AC_ANY,
    DWC_ERROR_NETWORK,
    DWC_ERROR_GHTTP_ANY,
    DWC_ERROR_DISCONNECTED,
    DWC_ERROR_FATAL,
    DWC_ERROR_FRIENDS_SHORTAGE,
    DWC_ERROR_NOT_FRIEND_SERVER,
    DWC_ERROR_SERVER_FULL,
    DWC_ERROR_ND_ANY,
    DWC_ERROR_ND_HTTP,
    DWC_ERROR_SVL_ANY,
    DWC_ERROR_SVL_HTTP,
    DWC_ERROR_PROF_PARSE_ERR,
    DWC_ERROR_PROF_HTTP,
    DWC_ERROR_DB_ANY,
    DWC_ERROR_SC_CONNECT_BLOCK,
    DWC_ERROR_NETWORK_LIGHT,
    DWC_ERROR_COUNT,
} DWCError;

int DWCi_HandleGPError(int error);

#ifdef __cplusplus
}
#endif