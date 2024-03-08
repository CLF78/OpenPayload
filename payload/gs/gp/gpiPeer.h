#include <common/Common.h>
#include <gs/darray.h>
#include <gs/gp/gpiBuffer.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GPIPeer GPIPeer;

struct GPIPeer {
    int state;
    int initiated;
    int socket;
    int profile;
    int timeout;
    int nackCount;
    GPIBuffer inputBuffer;
    GPIBuffer outputBuffer;
    DArray messages;
    GPIPeer* next;
};

#ifdef __cplusplus
}
#endif
