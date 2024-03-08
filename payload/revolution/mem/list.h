#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* prev;
    void* next;
} MEMLink;

typedef struct {
    void* head;
    void* tail;
    u16 count;
    u16 offset;
} MEMList;

#ifdef __cplusplus
}
#endif
