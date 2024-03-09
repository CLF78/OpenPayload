#include <common/Common.hpp>
#include <dwc/dwc_base64.h>
#include <dwc/dwc_match.h>
#include <game/system/RKSystem.hpp>
#include <gs/gp/gpi.h>
#include <nw4r/ut/Lock.hpp>
#include <platform/new.hpp>
#include <platform/stdio.h>
#include <platform/string.h>
#include <wiimmfi/Status.hpp>

namespace Wiimmfi {
namespace Status {

char* sToken;
char sScrambledToken[96];

void DecodeToken(const char* encodedToken) {

    // Get the decoded token size
    int encodedLen = strlen(encodedToken);
    int decodedLen = DWC_Base64Decode(encodedToken, encodedLen, nullptr, 0);
    sToken = new (KAMEK_HEAP, 32) char[decodedLen+1];

    // Decode the token
    decodedLen = DWC_Base64Decode(encodedToken, encodedLen, sToken, decodedLen);
    sToken[decodedLen] = '\0';

    // Start by filling an ASCII table
    for (int i = 0; i < sizeof(sScrambledToken) - 1; i++) {
        sScrambledToken[i] = i + ' ';
    }

    // Check if the token was decoded correctly
    if (decodedLen > 0) {

        // Run ASCII substitution
        const char key[] = "0123456789,abcdefghijklmnopqrstuvwxyz|=+-_";
        for (int i = 0; i < decodedLen && i < sizeof(key); i++) {
            char c = sToken[i];
            char pos = key[i];
            sScrambledToken[pos - ' '] = c;
        }
    }
}

void ScrambleMessage(char* msg, int msgLen) {

    // Check that the token was obtained, if not bail
    if (!sToken)
        return;

    // Scramble the message otherwise
    for (int i = 0; i < msgLen; i++) {
        u8 c = msg[i] - ' ';
        if (c < sizeof(sScrambledToken)-1)
            msg[i] = sScrambledToken[c];
    }
}

void SendMessage(const char* key, const char* value, int integerValue) {

    // Check that the match control structure exists
    if (!stpMatchCnt || !stpMatchCnt->gpConnection)
        return;

    // Get connection
    GPConnection conn = stpMatchCnt->gpConnection;
    if (!*conn) {
        DEBUG_REPORT("[WIIMMFI_REPORT] Connection not initialized, discarding message\n")
        return;
    }

    // Print the message to the buffer
    DEBUG_REPORT("[WIIMMFI_REPORT] %s=%s,%d\n", key, value, integerValue)
    char buffer[599];
    int len = snprintf(buffer, sizeof(buffer), "\\xy\\%s\\v\\1\\id\\%d\\msg\\%s\\final\\",
                       key, integerValue, value);

    // If the printed string did not fit in the buffer, bail
    if (len > sizeof(buffer)) {
        DEBUG_REPORT("[WIIMMFI_REPORT] Message length exceeded buffer (size=%d), discarding\n", len)
        return;
    }

    // Scramble the message
    ScrambleMessage(buffer + sizeof("\\xy\\")-1, len - sizeof("\\final\\") - sizeof("\\xy\\") - 1);

    // Lock interrupts and append message
    {
        nw4r::ut::AutoInterruptLock lock;
        gpiAppendStringToBuffer(conn, &(*conn)->outputBuffer, buffer);
    }
}

} // namespace Status
} // namespace Wiimmfi
