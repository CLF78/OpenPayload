#include <common/Common.hpp>
#include <dwc/dwc_base64.h>
#include <revolution/ios.h>
#include <revolutionex/nhttp/NHTTPInternal.h>

namespace Wiimmfi {
namespace Auth {

    ///////////////
    // Constants //
    ///////////////

    // The possible console types
    enum ConsoleType {
        CONSOLE_WII = 0x0000,
        CONSOLE_WII_MINI = 0x0C01,
        CONSOLE_WII_U = 0xCAFE,
        CONSOLE_DOLPHIN = 0xFFFF,
    };

    // The payload version we pretend to be on
    // This is because the server currently does not let us join with the correct version number
    static const char PAYLOAD_VERSION[] = "96";

    // The patcher type
    // This is the pre-encoded version of "OpenPayload"
    static const char PATCHER_TYPE[] = "T3BlblBheWxvYWQA";

    // The heading of each response type
    static const char RESPONSE_P2PPORT[] = "p2pport=";
    static const char RESPONSE_CONSOLE_ASSIGN[] = "msg=";
    static const char RESPONSE_TOKEN[] = "xy=";

    ///////////////
    // Functions //
    ///////////////

    // Append the aforementioned parameters to the login request, along with some others
    void AppendAuthParameters(NHTTPReq* req);

    // Parses the login response
    void ParseAuthResponse(const char* response);

    ///////////////
    // Variables //
    ///////////////

    // The base64-encoded console certificate
    extern char sConsoleCert[DWC_Base64GetEncodedSize(IOSECCCertSize)+1];

    // The console assignment message
    // We cannot use an offline message since we need a component of the received one for assignment to work
    extern wchar_t* sConsoleAssignMessage;

} // namespace Auth
} // namespace Wiimmfi
