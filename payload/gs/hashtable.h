#include <common/Common.h>
#include <gs/darray.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*TableFreeFunc)(void* elem);
typedef int (*TableHashFunc)(void* elem, int);
typedef int (*TableCompareFunc)(void* elem1, void* elem2);

typedef struct {
    DArray* buckets;
    int numBuckets;
    TableFreeFunc freeFunc;
    TableHashFunc hashFunc;
    TableCompareFunc compareFunc;
} HashImplementation;

typedef HashImplementation* HashTable;

#ifdef __cplusplus
}
#endif
