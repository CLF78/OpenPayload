
#include <common/Common.h>
#include <gs/gt2/gt2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct GTI2Socket GTI2Socket, *GT2Socket;
typedef struct GTI2Connection GTI2Connection, *GT2Connection;

typedef void (*GT2SocketErrorCallback)(GT2Socket sock);
typedef void (*GT2ConnectAttemptCallback)(GT2Socket sock, GT2Connection conn, u32 ip, u16 port,
                                          int latency, const char* msg, int msgLen);
typedef void (*GT2ConnectedCallback)(GT2Connection conn, GT2Result, const char* msg, int msgLen);
typedef void (*GT2ReceivedCallback)(GT2Connection conn, u8* msg, int msgLen, int isReliable);
typedef void (*GT2ClosedCallback)(GT2Connection conn, GT2CloseReason reason);
typedef void (*GT2PingCallback)(GT2Connection conn, int latency);
typedef void (*GT2DumpCallback)(GT2Socket sock, GT2Connection conn, u32 ip, u16 port,
                                int latency, u8* msg, int msgLen);
typedef int (*GT2UnrecognizedMessageCallback)(GT2Socket sock, u32 ip, u16 port, u8* msg, int msgLen);

typedef struct {
    GT2ConnectedCallback connectedCb;
    GT2ReceivedCallback receivedCb;
    GT2ClosedCallback closeCb;
    GT2PingCallback pingCb;
} GT2Callbacks;

#ifdef __cplusplus
}
#endif
