#include <common/Common.hpp>

namespace Wiimmfi {
namespace MatchCommand {

    ////////////////
    // Structures //
    ////////////////

    // The structure for DWC_CMD_CONN_FAIL_MTX
    // This command is sent by client A to the host to tell them client B could not complete NATNEG with them
    // The host then sends a NEW_PID_AID command to client B to try and solve the problem quicker
    struct DWCMatchCommandConnFailMtx {
        u32 connFailMtx;
    };

    // The structure for DWC_CMD_CONN_MTX
    // This command is sent by client A to client B to inform them of the aids connected to them
    // This is used by client B to route network packets through a random aid (chosen among those connected to
    // A and including the host) in case P2P fails. The entire feature seems to be unused, however
    struct DWCMatchCommandConnMtx {
        u32 connMtx;
    };

    ///////////////
    // Functions //
    ///////////////

    // Parse custom commands
    // Returns true if the command was recognized and parsed
    bool ProcessRecvMatchCommand(u8 cmd, int profileId, u32 publicIp, u16 publicPort, void* cmdData, int dataLen);

    // Sends a DWC_CMD_CONN_FAIL_MTX command to the host
    // The data required for the command is in the arguments
    void SendConnFailMtxCommand(u32 aidsConnectedToHost, u32 aidsConnectedToMe);

    // Sends a DWC_CMD_CONN_MTX command to all the connected clients
    // The data required for the command is in the arguments
    void SendConnMtxCommand(u32 aidsConnectedToMe);

} // namespace MatchCommand
} // namespace Wiimmfi
