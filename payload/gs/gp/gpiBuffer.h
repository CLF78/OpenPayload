#include <common/Common.h>
#include <gs/gp/gp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* buffer;
    int size;
    int len;
    int pos;
} GPIBuffer;

GPResult gpiAppendStringToBuffer(GPConnection connection, GPIBuffer* outputBuffer, const char* buffer);

#ifdef __cplusplus
}
#endif
