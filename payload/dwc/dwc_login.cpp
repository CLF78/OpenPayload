#include <common/Common.h>
#include <dwc/dwc_login.h>
#include <dwc/dwc_report.h>
#include <wiimmfi/Natify.hpp>

// Ported from NitroDWC decompilation
inline u32 DWCi_Acc_GetMaskBits(u32 data, u32 shift, u32 mask) {
    return ((data >> shift) & mask);
}

// Ported from NitroDWC decompilation
BOOL DWCi_Acc_SetMaskBits(u32* ptr, u32 data, u32 shift, u32 mask) {
    if ((data & ~mask) != 0)
        return FALSE;

    *ptr = (*ptr & ~(mask << shift)) | (data << shift);
    return TRUE;
}

// Ported from NitroDWC decompilation
u32 DWCi_Acc_GetFlags(const DWCAccFlag* userdata) {
    return DWCi_Acc_GetMaskBits(userdata->flags, DWC_ACC_FLAGS_SHIFT, DWC_ACC_FLAGS_MASK);
}

// Ported from NitroDWC decompilation
void DWCi_Acc_SetFlags(DWCAccFlag* userdata, u32 flags) {
    DWCi_Acc_SetMaskBits(&userdata->flags, flags, DWC_ACC_FLAGS_SHIFT, DWC_ACC_FLAGS_MASK);
}

// Ported from NitroDWC decompilation
void DWCi_Acc_SetFlag_DataType(DWCAccFlag* userdata, int type) {
    u32 flags = DWCi_Acc_GetFlags(userdata);
    flags = (flags & ~DWC_FRIENDDATA_MASK) | type;
    DWCi_Acc_SetFlags(userdata, flags);
}

/////////////////////
// Error 60000 Fix //
/////////////////////

// DWCi_GPConnectCallback() patch
// Clear the Profile ID if error 60000 is encountered
// Credits: Wiimmfi
kmBranchDefCpp(0x800D05A8, 0x800D0610, void) {

    // Debug report
    DEBUG_REPORT("[WIIMMFI] Invalid profile ID detected, requesting new one\n")

    // Set state to GPGETINFO (AKA lastname acquisition during GP login)
    stpLoginCnt->state = DWC_LOGIN_STATE_GPGETINFO;

    // Set the user ID and the data type
    DWCi_Acc_SetUserId(&stpLoginCnt->tempLoginId, DWCi_Auth_GetConsoleUserId());
    DWCi_Acc_SetFlag_DataType((DWCAccFlag*)&stpLoginCnt->tempLoginId, DWC_FRIENDDATA_LOGIN_ID);

    // Copy temp loginId from pseudo loginId and mark user data as dirty
    stpLoginCnt->tempLoginId.playerId = stpLoginCnt->userdata->pseudo.playerId;
    stpLoginCnt->userdata->flag = DWC_USER_DATA_FLAG_DIRTY;
}

/////////////////////////
// NATify Improvements //
/////////////////////////

// DWCi_RemoteLoginProcess() patch
// Start custom NATify procedure
// Credits: Wiimmfi
kmCallDefCpp(0x800D086C, void, DWCReportFlag level, const char* str) {

    // Original call
    DWC_Printf(level, str);

    // Start NATify
    Wiimmfi::Natify::Start();
}
