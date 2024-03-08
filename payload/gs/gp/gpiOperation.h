#include <common/Common.h>
#include <gs/gp/gpiCallback.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GPIOperation GPIOperation;

struct GPIOperation {
    int type;
    void* data;
    int blocking;
    GPICallback callback;
    int state;
    int id;
    int result;
    GPIOperation* next;
};

#ifdef __cplusplus
}
#endif
