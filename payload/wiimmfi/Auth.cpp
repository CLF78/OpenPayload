#include <common/Common.hpp>
#include <dwc/dwc_base64.h>
#include <platform/stdio.h>
#include <platform/stdlib.h>
#include <platform/string.h>
#include <revolution/base/PPCArch.h>
#include <revolution/es/es.h>
#include <revolutionex/nhttp/NHTTP.h>
#include <wiimmfi/Auth.hpp>
#include <wiimmfi/Port.hpp>
#include <wiimmfi/Status.hpp>
#include <DolphinDevice.hpp>
#include <ModSupport.hpp>

namespace Wiimmfi {
namespace Auth {

char sConsoleCert[DWC_Base64GetEncodedSize(IOSECCCertSize)+1];
char sConsoleAssignMessageBuffer[796];
wchar_t* sConsoleAssignMessage;

void AppendAuthParameters(NHTTPReq* req) {

    // Send payload version
    DEBUG_REPORT("[WIIMMFI_AUTH] Started auth procedure\n")
    DEBUG_REPORT("[WIIMMFI_AUTH] Sending payload version: %s\n", PAYLOAD_VERSION)
    NHTTPAddPostDataAscii(req, "_payload_ver", PAYLOAD_VERSION);

    // Get the console's certificate (the real authentication method)
    // Only do this operation once
    static bool sCertObtained = false;

    if (!sCertObtained) {
        ALIGN(32) char certBuf[IOSECCCertSize]; // IOS requires the output to be aligned by 32
        s32 result = ES_GetDeviceCert((u8*)certBuf);

        // If IOS call fails, bail
        if (result != ES_ERR_OK) {
            DEBUG_REPORT("[WIIMMFI_AUTH] Failed to get device certificate\n")
            return;
        }

        // Encode it
        int len = DWC_Base64Encode(certBuf, sizeof(certBuf), sConsoleCert, sizeof(sConsoleCert));
        sConsoleCert[len] = '\0';

        // Mark data as obtained successfully
        sCertObtained = true;
    } else {
        DEBUG_REPORT("[WIIMMFI_AUTH] Already obtained device certificate\n")
    }

    // Send the certificate
    DEBUG_REPORT("[WIIMMFI_AUTH] Sending certificate: %s\n", sConsoleCert)
    NHTTPAddPostDataAscii(req, "_val1", sConsoleCert);

    // Send patcher string
    // Do not send the patcher version, as that is only used with WSZST-patched DOLs
    DEBUG_REPORT("[WIIMMFI_AUTH] Sending patcher type: %s\n", PATCHER_TYPE)
    NHTTPAddPostDataAscii(req, "_patcher", PATCHER_TYPE);

    // Send the console type (but not the actual one)
    // Wiimmfi here does a couple of things:
    // - Read 2 bytes at 0xCD8005A0
    // * On Wii, this is a mirror of 0xCD8001A0, a random clock register (PLLSYS) whose value will be 0xFFFF
    // * On other platforms, this is a register named LT_CHIPREVID, and the value will be 0xCAFE
    // - Try to open /title/00000001/00000002/data/macaddr.bin
    // * If the file exists, the console is a Wii Mini, so set the console type to 0x0C01
    // - Get the count of titles with id 0000000100000200
    // * The title is BC-NAND, which is vWii only, so if present set the console type to 0xCAFE
    // We will pretend to be a regular Wii console on the PAL game
    DEBUG_REPORT("[WIIMMFI_AUTH] Sending console type and region: %s\n", CONSOLE_TYPE)
    NHTTPAddPostDataAscii(req, "_console", CONSOLE_TYPE);

    // Send the device ID XOR'd with Dolphin's default value
    char deviceIdBuffer[28];
    sprintf(deviceIdBuffer, "%08x-%08x-%08x", PPCGetECID_U() ^ DEFAULT_ECID_U,
                                              PPCGetECID_M() ^ DEFAULT_ECID_M,
                                              PPCGetECID_L() ^ DEFAULT_ECID_L);
    DEBUG_REPORT("[WIIMMFI_AUTH] Sending device ID: %s\n", deviceIdBuffer)
    NHTTPAddPostDataAscii(req, "_deviceID", deviceIdBuffer);

    // Check if the user is on Dolphin by opening its device, and if so send the Dolphin version
    if (DolphinDevice::Open()) {
        const char* version = DolphinDevice::GetVersion();
        if (version) {
            DEBUG_REPORT("[WIIMMFI_AUTH] Sending Dolphin version: %s\n", version)
            NHTTPAddPostDataAscii(req, "_dolphin_ver", version);
        } else {
            DEBUG_REPORT("[WIIMMFI_AUTH] Failed to get Dolphin version\n")
        }
    }

    // If the user has set an UPNP port, send it over
    u16 customPort = ModSupport::GetCustomUPNPPort();
    if (customPort) {

        // Convert to string
        char portBuffer[6];
        snprintf(portBuffer, sizeof(portBuffer), "%d", customPort);
        DEBUG_REPORT("[WIIMMFI_AUTH] Sending user port: %s\n", portBuffer)

        // Encode to Base64
        char b64UserPort[DWC_Base64GetEncodedSize(sizeof(portBuffer))+1];
        int len = DWC_Base64Encode(portBuffer, sizeof(portBuffer), b64UserPort, sizeof(b64UserPort));
        b64UserPort[len] = '\0';

        // Send it
        NHTTPAddPostDataAscii(req, "_upnpport", b64UserPort);
    }

    DEBUG_REPORT("[WIIMMFI_AUTH] Auth completed!\n")
}

void ParseAuthResponse(const char* response) {

    // Response type: P2P port
    // Store the UPNP port to be used
    if (strstartw(response, RESPONSE_P2PPORT)) {
        strshift(response, RESPONSE_P2PPORT);
        DEBUG_REPORT("[WIIMMFI_AUTH] Received P2P port: %s\n", response);
        Wiimmfi::Port::sPort = atoi(response);
    }

    // Response type: console assignment message
    // Decode the message and store it for display later
    else if (strstartw(response, RESPONSE_CONSOLE_ASSIGN)) {
        strshift(response, RESPONSE_CONSOLE_ASSIGN);
        DEBUG_REPORT("[WIIMMFI_AUTH] Received console assignment message\n")

        // Get encoded and decoded message length
        // If it doesn't fit the buffer, bail
        int encodedLen = strlen(response);
        int decodedLen = DWC_Base64Decode(response, encodedLen, nullptr, 0);
        if (decodedLen > sizeof(sConsoleAssignMessageBuffer) - sizeof(wchar_t)) {
            DEBUG_REPORT("[WIIMMFI_AUTH] Message exceeds buffer size, discarding\n")
            return;
        }

        // Decode the message and set the pointer to indicate a successful decode
        // The message is already in UTF-16 format, so we do not need to convert it
        decodedLen = DWC_Base64Decode(response, encodedLen, sConsoleAssignMessageBuffer,
                                      sizeof(sConsoleAssignMessageBuffer) - sizeof(wchar_t));
        sConsoleAssignMessageBuffer[decodedLen] = '\0';
        sConsoleAssignMessageBuffer[decodedLen+1] = '\0';
        sConsoleAssignMessage = (wchar_t*)sConsoleAssignMessageBuffer;
    }

    // Response type: token
    // Decode the token and scramble it
    else if (strstartw(response, RESPONSE_TOKEN)) {
        strshift(response, RESPONSE_TOKEN);
        DEBUG_REPORT("[WIIMMFI_AUTH] Received token\n")
        Status::DecodeToken(response);
    }

    else {
        DEBUG_REPORT("[WIIMMFI_AUTH] Unknown response: %s\n", response)
    }
}

} // namespace Auth
} // namespace Wiimmfi
