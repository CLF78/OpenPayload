#include <common/Common.hpp>
#include <gs/common/gsSocketRevolution.h>
#include <gs/qr2/qr2.h>
#include <revolutionex/so/SOBasic.h>
#include <wiimmfi/Challenge.hpp>

/////////////////////////////
// Wiimmfi Challenge Check //
/////////////////////////////

// send_heartbeat() patch
// Send the login challenge
// Credits: Wiimmfi
kmCallDefCpp(0x80111534, void, int socket, qr2_buffer* buffer, int bufferLength, int flags,
             const SOSockAddrIn* addr, u8 toLen) {

    // Store the challenge into the buffer and send it
    Wiimmfi::Challenge::Send(buffer);
    sendto(socket, buffer->data, buffer->dataSize, flags, addr, toLen);
}
