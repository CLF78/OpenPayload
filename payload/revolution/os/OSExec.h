#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 valid;
    u32 resetCode;
    u32 bootDol;
    void* arenaLo;
    void* arenaHi;
    u32 argsUseDefault;
    void* args;
} OSExecParams;

#ifdef __cplusplus
}
#endif
