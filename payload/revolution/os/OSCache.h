#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void __flush_cache(void* buffer, u32 size);

void DCStoreRange(void* addr, u32 nBytes);

#ifdef __cplusplus
}
#endif
