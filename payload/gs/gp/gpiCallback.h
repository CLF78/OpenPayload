#include <common/Common.h>
#include <gs/gp/gp.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GPICallbackData GPICallbackData;

typedef struct {
    GPCallback callback;
    void* param;
} GPICallback;

struct GPICallbackData {
    GPICallback callback;
    void* arg;
    int type;
    int operationID;
    GPICallbackData* next;
};

#ifdef __cplusplus
}
#endif
