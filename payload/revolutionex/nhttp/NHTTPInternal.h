#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NHTTPRes NHTTPRes;
typedef struct NHTTPReq NHTTPReq;
typedef struct NHTTPReqList NHTTPReqList;
typedef struct NHTTPDataList NHTTPDataList;

typedef void* (*NHTTPAlloc)(u32 size, int align);
typedef void (*NHTTPFree)(void* ptr);
typedef int (*NHTTPPostSend)(const char* label, char** value, u32* length, int offset, void* param);

struct NHTTPReq {
    volatile int doCancel;
    int isStarted;
    int isSSL;
    int isProxy;
    int isRawData;

    int hostLen;
    int hostDescLen;

    int method;
    int port;
    char* url;
    char* hostname;

    NHTTPRes* res;
    NHTTPDataList* headerList;
    NHTTPDataList* postDataList;

    char tagPost[20];

    char basicUsernamePassword[90];
    int basicUsernamePasswordLen;

    int sslId;
    const char* clientCert;
    size_t clientCertSize;
    const char* privateKey;
    size_t privateKeySize;
    const char* rootCA;
    size_t rootCASize;
    int useClientCertDefault;
    u32 verifyOption;
    int encodingType;

    u32 disableVerifyOption;
    u32 rootCAId;
    u32 clientCertId;

    char proxyAddr[256];
    int proxyPort;
    char proxyUsernamePassword[90];
    int proxyUsernamePasswordLen;

    u32 soRecvSize;

    const char* rawPostData;
    u32 rawPostDataLen;

    NHTTPPostSend postSendCallback;
};

struct NHTTPReqList {
    NHTTPReqList* prev;
    NHTTPReqList* next;
    int id;
    NHTTPReq* req;
    void* socket;
};

struct NHTTPDataList {
    struct NHTTPDataList* prev;
    struct NHTTPDataList* next;
    const char* label;
    const char* value;
    u32 length;
    int isBinary;
};

#ifdef __cplusplus
}
#endif
