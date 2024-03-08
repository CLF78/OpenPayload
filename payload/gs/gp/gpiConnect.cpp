#include <common/Common.hpp>
#include <wiimmfi/Reporting.hpp>

///////////////////////
// Wiimmfi Telemetry //
///////////////////////

// gpiSendLogin() patch
// Report the signature and certificate to the server
// Credits: Wiimmfi
kmBranchDefCpp(0x801007D8, NULL, int, int ret) {
    Wiimmfi::Reporting::ReportSignatureAndCert();
    return ret;
}
