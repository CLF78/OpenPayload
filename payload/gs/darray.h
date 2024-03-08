#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ArrayFreeFunc)(void* element);

typedef struct {
    int count;
    int capacity;
    int elemSize;
    int growBy;
    ArrayFreeFunc elemFreeFunc;
    void* list;
} DArrayImplementation;

typedef DArrayImplementation* DArray;

#ifdef __cplusplus
}
#endif
