#include <common/Common.hpp>
#include <wiimmfi/RoomStall.hpp>

//////////////////////////////////
// Online Room Stall Prevention //
//////////////////////////////////

// RKNetSELECTHandler::calc() patch
// Update the timer every frame and kick if necessary
// Credits: Wiimmfi
kmCallDefCpp(0x80660330, bool) {
    Wiimmfi::RoomStall::Update();
    return true; // Not calling the original function here because the result would always be true
}

// RKNetSELECTHandler::getStaticInstance() patch
// Initialize the timer
// Credits: Wiimmfi
kmBranchDefCpp(0x8065FF5C, NULL, void) {
    Wiimmfi::RoomStall::Init();
}
