#include <common/Common.hpp>

namespace Wiimmfi {
namespace Status {

    ///////////////
    // Constants //
    ///////////////

    // Header and terminator string for each status report
    static const char STATUS_HEADER[] = "\\xy\\";
    static const char STATUS_TERMINATOR[] = "\\final\\";

    ///////////////
    // Functions //
    ///////////////

    // Decode the token received from the server and scrambles it
    void DecodeToken(const char* encodedToken);

    // Sends a status message to the server
    void SendMessage(const char* key, const char* value, int integerValue = -1);

    ///////////////
    // Variables //
    ///////////////

    // The token received on login (will be deleted on network shutdown)
    extern char* sToken;

} // namespace Port
} // namespace Wiimmfi
