#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    GSIAC_WAITING,
    GSIAC_AVAILABLE,
    GSIAC_UNAVAILABLE,
    GSIAC_TEMPORARILY_UNAVAILABLE,
} GSIACResult;

extern int __GSIACResult;

#ifdef __cplusplus
}
#endif
