#include <common/Common.hpp>
#include <dwc/dwc_node.h>
#include <gs/gt2/gt2Main.h>

namespace Wiimmfi {
namespace Natneg {

    // Updates the NATNEG timers for Fast NATNEG
    void CalcTimers(bool connectedToHost);

    // Override of DWCi_GT2ConnectAttemptCallback to accept multiple incoming connections at once
    void ConnectAttemptCallback(GT2Socket socket, GT2Connection conn, u32 ip, u16 port, int latency,
                                const char* msg, int msgLen);

    // Override of DWCi_GT2ConnectedCallback to accept multiple incoming connections at once
    void ConnectedCallback(GT2Connection conn, GT2Result result, const char* msg, int msgLen);

    // Improves the next NATNEG node choosing algorithm used by Nintendo by choosing the lowest
    // retry time and ignoring the maximum retry count limit
    DWCNodeInfo* GetNextMeshMakingNode();

    // Checks NATNEG attempts to prevent the host from disconnecting due to repeated NATNEG failures
    // with the same client
    // Returns true if the attempt should count toward the Error 86420 threshold
    bool PreventRepeatNATNEGFail(u32 failedPid);

    // Attempt to recover from a SYN-ACK timeout (i think)
    void RecoverSynAckTimeout();

    // Stops NATNEG after a certain amount of time has passed (only applies to guests)
    void StopNATNEGAfterTime();

} // namespace Natneg
} // namespace Wiimmfi
