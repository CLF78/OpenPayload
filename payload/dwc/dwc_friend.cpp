#include <common/Common.h>
#include <game/net/RKNetStatusData.hpp>
#include <wiimmfi/Natify.hpp>

///////////////////////////////////////
// Friend Status Buffer Overflow Fix //
///////////////////////////////////////

// DWC_GetFriendStatusData() patch
// Enforce the destination buffer size to prevent an overflow
// Credits: Wiimmfi
kmWrite32(0x800CE220, 0x38C00000 | sizeof(RKNetStatusData[2]));

/////////////////////////
// NATify Improvements //
/////////////////////////

// DWCi_FriendProcess() patch
// Update custom NATify procedure
// Credits: Wiimmfi
kmBranchDefCpp(0x800CE7A4, NULL, void) {
    Wiimmfi::Natify::Update();
}
