#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOSECCCertSize 384
#define IOSECCSigSize 60

typedef enum {
    IPC_OK         = 0,
    IPC_EACCES     = -1,
    IPC_EEXIST     = -2,
    IPC_EINVAL     = -4,
    IPC_ENOENT     = -6,
    IPC_EQUEUEFULL = -8,
    IPC_ENOMEM     = -22,
} IPCResult;

typedef enum {
    IPC_OPEN_NONE  = BIT_FLAG(-1),
    IPC_OPEN_READ  = BIT_FLAG(0),
    IPC_OPEN_WRITE = BIT_FLAG(1),
    IPC_OPEN_RW    = IPC_OPEN_READ | IPC_OPEN_WRITE,
} IPCOpenFlags;

typedef struct {
    void* data;
    u32 size;
} IOSIoVector;

s32 IOS_Open(const char* path, u32 flags);
s32 IOS_Ioctlv(s32 fd, s32 cmd, u32 inputCount, u32 outputCount, IOSIoVector* vector);
s32 IOS_Close(s32 fd);

#ifdef __cplusplus
}
#endif
