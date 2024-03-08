#include <common/Common.hpp>
#include <dwc/dwc_main.h>
#include <gs/gt2/gt2Main.h>
#include <gs/gt2/gt2Utility.h>
#include <wiimmfi/ConnectionMatrix.hpp>
#include <wiimmfi/Natneg.hpp>
#include <wiimmfi/Port.hpp>

/////////////////
// Fast NATNEG //
/////////////////

// DWC_InitFriendsMatch() patch
// Replace ConnectedCallback to accept incoming connections in more cases
// Credits: Wiimmfi
kmBranchDefCpp(0x800D0FE8, NULL, void) {
    stpDwcCnt->callbacks.connectedCb = &Wiimmfi::Natneg::ConnectedCallback;
}

// DWCi_GT2Startup() patch
// Replace ConnectAttemptCallback to accept incoming connections in more cases
// Credits: Wiimmfi
kmCallDefCpp(0x800D28CC, void, GT2Socket sock, GT2ConnectAttemptCallback callback) {
    gt2Listen(sock, Wiimmfi::Natneg::ConnectAttemptCallback);
}

// DWCi_MatchedCallback() patch
// Update NATNEG timers
// Credits: Wiimmfi
kmCallDefCpp(0x800D3188, void, DWCError error, int cancel, int self, int isServer, int index, void* param) {

    // Original call
    stpDwcCnt->userMatchedCallback(error, cancel, self, isServer, index, param);

    // Update NATNEG with the self value
    Wiimmfi::Natneg::CalcTimers(self);
}

/////////////////////////////////////
// Fast NATNEG / Wiimmfi Telemetry //
/////////////////////////////////////

// DWCi_GT2ClosedProcess() patch
// Update the connection matrix when a connection is closed
// Credits: Wiimmfi
kmBranch(0x800D3F1C, Wiimmfi::ConnectionMatrix::Update);

//////////////////////////
// Wiimmfi Port Binding //
//////////////////////////

// DWCi_GT2Startup() patch
// Use the server-provided port for GT2Sockets
// Credits: Wiimmfi
kmCallDefCpp(0x800D2884, char*, u32 ip, u16 port, char* string) {

    // Override port if set
    if (Wiimmfi::Port::sPort)
        port = Wiimmfi::Port::sPort;

    // Original call
    return gt2AddressToString(ip, port, string);
}
