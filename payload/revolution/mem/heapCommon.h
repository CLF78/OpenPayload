#include <common/Common.h>
#include <revolution/mem/list.h>
#include <revolution/os/OSMutex.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u32 signature;
    MEMLink link;
    MEMList childList;
    void* heapStart;
    void* heapEnd;
    OSMutex mutex;
    u8 reserved[3];
    u8 optFlag;
} MEMiHeapHead;

#ifdef __cplusplus
}
#endif
