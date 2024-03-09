#include <common/Common.hpp>
#include <dwc/dwc_base64.h>
#include <revolution/ios.h>
#include <revolutionex/nhttp/NHTTPInternal.h>

// TODO Depending on how the reveal goes, change this to provide real information
namespace Wiimmfi {
namespace Auth {

    ///////////////
    // Constants //
    ///////////////

    // The payload version we pretend to be on
    // This is because the server currently does not let us join with the correct version number
    static const char PAYLOAD_VERSION[] = "96";

    // The patcher type
    // This is the pre-encoded version of "OpenPayload"
    static const char PATCHER_TYPE[] = "T3BlblBheWxvYWQA";

    // The console type and region we pretend to be on, as Wiimmfi doesn't need this information
    // This is the pre-computed string for regular Wii on the PAL version
    static const char CONSOLE_TYPE[] = "ffff-P";

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
