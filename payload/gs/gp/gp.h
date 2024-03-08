#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GPIConnection GPIConnection, **GPConnection;

typedef void (*GPCallback)(GPConnection connection, void* arg, void* param);

typedef enum {
    GP_ERROR_NONE,
    GP_ERROR_MEMORY,
    GP_ERROR_PARAMETER,
    GP_ERROR_NETWORK,
    GP_ERROR_SERVER,
} GPResult;

#ifdef __cplusplus
}
#endif
