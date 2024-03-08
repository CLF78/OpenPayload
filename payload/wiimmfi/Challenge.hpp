#include <common/Common.hpp>
#include <gs/qr2/qr2.h>

namespace Wiimmfi {
namespace Challenge {

    // Saves the received challenge
    void Save(const char* challenge);

    // Sends the saved challenge
    void Send(qr2_buffer* buffer);

} // namespace Challenge
} // namespace Wiimmfi
