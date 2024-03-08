#include <common/Common.h>
#include <gs/darray.h>
#include <gs/hashtable.h>
#include <gs/gt2/gt2Buffer.h>
#include <gs/gt2/gt2Callback.h>

#ifdef __cplusplus
extern "C" {
#endif

struct GTI2Socket {
    int socket;
    u32 ip;
    u16 port;
    // 2 bytes padding

    HashTable connections;
    DArray closedConnections;
    int close;
    int error;
    int callbackLevel;

    GT2ConnectAttemptCallback connectAttemptCallback;
    GT2SocketErrorCallback socketErrorCallback;
    GT2DumpCallback sendDumpCallback;
    GT2DumpCallback receiveDumpCallback;
    GT2UnrecognizedMessageCallback unrecognizedMsgCallback;

    void* data;
    u32 sendBufferSize;
    u32 recvBufferSize;

    GT2Protocol protocolType;
    int protocolOffset;
    int broadcastEnabled;
};

struct GTI2Connection {
    u32 ip;
    u16 port;
    u8 aid; // custom field
    // 1 byte padding

    GTI2Socket* socket;
    GT2SocketState state;
    int initiated;
    int freeAtAcceptReject;
    GT2Result result;
    u32 startTime;
    u32 timeout;
    int callbackLevel;
    GT2Callbacks callbacks;
    char * initialMessage;
    int initialMessageLen;
    void* data;
    GTI2Buffer incomingBuffer;
    GTI2Buffer outgoingBuffer;
    DArray incomingBufferMessages;
    DArray outgoingBufferMessages;
    u16 serialNumber;
    u16 expectedSerialNumber;
    char response[32];
    u32 lastSend;
    u32 challengeTime;
    int pendingAck;
    u32 pendingAckTime;
    DArray sendFilters;
    DArray receiveFilters;
};

GT2Result gt2Connect(GT2Socket socket, GT2Connection* connection, const char* remoteAddress,
                     const char* msg, int msgLen, int timeout, GT2Callbacks* callbacks, int blocking);

BOOL gt2Accept(GT2Connection connection, GT2Callbacks* callbacks);
void gt2Listen(GT2Socket socket, GT2ConnectAttemptCallback callback);
void gt2Reject(GT2Connection connection, const char* msg, int msgLen);

#ifdef __cplusplus
}
#endif
