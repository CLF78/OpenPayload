#include <common/Common.hpp>
#include <dwc/dwc_report.h>
#include <platform/string.h>
#include <revolution/sc.h>
#include <revolutionex/nhttp/NHTTP.h>
#include <wiimmfi/Auth.hpp>
#include <wiimmfi/Challenge.hpp>
#include <DolphinDevice.hpp>

////////////////////////////
// Wiimmfi Authentication //
////////////////////////////

// DWCi_Auth_SendRequest() patch
// Insert custom authentication parameters
// Credits: Wiimmfi
kmCallDefCpp(0x800EDEE8, void, NHTTPReq* req, const char* key, const char* val) {

    // Original call
    NHTTPAddPostDataAscii(req, key, val);

    // Send the required extra data
    Wiimmfi::Auth::AppendAuthParameters(req);
}

// DWCi_Auth_SendRequest() patch
// Report the product code from the imported NAND on Dolphin
// Credits: Wiimmfi
kmCallDefCpp(0x800EE098, const char*) {

    // Check if we're on Dolphin and use the dedicated IOCTL if so
    if (DolphinDevice::Open()) {
        const char* prodCode = DolphinDevice::GetRealProductCode();
        return (prodCode != nullptr) ? prodCode : SCGetProductCode();
    }

    // Else just call the original function
    return SCGetProductCode();
}

// DWCi_Auth_HandleResponse() patch
// Parse the custom response data
// Credits: Wiimmfi
kmCallDefCpp(0x800EEA08, void, DWCReportFlag level, const char* fmt, const char* arg) {

    // Original call
    DWC_Printf(level, fmt, arg);

    // Parse the extra response data
    Wiimmfi::Auth::ParseAuthResponse(arg);
}

/////////////////////////////
// Wiimmfi Challenge Check //
/////////////////////////////

// DWCi_Auth_HandleResponse() patch
// Save the login challenge
// Credits: Wiimmfi
kmCallDefCpp(0x800EE74C, void, char* dest, const char* src) {

    // Save the challenge both to the stack and the Wiimmfi buffers
    strcpy(dest, src);
    Wiimmfi::Challenge::Save(src);
}
