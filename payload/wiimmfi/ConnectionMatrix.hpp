#include <common/Common.hpp>

namespace Wiimmfi {
namespace ConnectionMatrix {

    ///////////////
    // Functions //
    ///////////////

    // Resets the received connection matrixes
    void ResetRecv();

    // Updates the connection matrix and shares it with the server and the connected clients
    void Update();

    ///////////////
    // Variables //
    ///////////////

    // The other clients' received connection matrixes
    // Currently unused
    extern u32 sRecvConnMtx[12];

} // namespace ConnectionMatrix
} // namespace Wiimmfi
