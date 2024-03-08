#include <common/Common.hpp>
#include <dwc/dwc_main.h>
#include <dwc/dwc_match.h>
#include <nw4r/ut/Lock.hpp>
#include <wiimmfi/ConnectionMatrix.hpp>
#include <wiimmfi/MatchCommand.hpp>
#include <wiimmfi/Reporting.hpp>

namespace Wiimmfi {
namespace ConnectionMatrix {

u32 sRecvConnMtx[12];

void ResetRecv() {

    // Get the node info for the aid, if it's null reset the received matrix
    for (int aid = 0; aid < 12; aid++) {
        if (!DWCi_NodeInfoList_GetNodeInfoForAid(aid))
            sRecvConnMtx[aid] = 0;
    }
}

void Update() {

    // Failsafe
    if (!stpMatchCnt)
        return;

    // Lock interrupts
    // Q: Why is this needed?
    nw4r::ut::AutoInterruptLock lock;

    // Compute the connection matrix
    u32 aidsConnectedToMe = 0;
    for (int i = 0; i < stpMatchCnt->nodeInfoList.nodeCount; i++) {
        u32 aid = stpMatchCnt->nodeInfoList.nodeInfos[i].aid;
        if (DWCi_GetGT2Connection(aid))
            aidsConnectedToMe |= 1 << i;
    }

    // Report it to the server and share it with the clients
    Reporting::ReportConnectionMatrix(aidsConnectedToMe);
    MatchCommand::SendConnMtxCommand(aidsConnectedToMe);
}

} // namespace ConnectionMatrix
} // namespace Wiimmfi
