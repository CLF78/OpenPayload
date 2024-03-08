#include <common/Common.hpp>
#include <game/net/RKNetRoomHandler.hpp>
#include <wiimmfi/Reporting.hpp>

///////////////////////
// Wiimmfi Telemetry //
///////////////////////

// FriendRoomMessageSelectPage::onModeBtnClick() patch
// Report friend room starts
kmCallDefCpp(0x805DCE34, void, RKNetROOMHandler* self, u32 data) {

    // Call telemetry function
    RKNetROOMPacketRaw packet(data);
    Wiimmfi::Reporting::ReportFriendRoomStart(&packet.packet);

    // Original call
    self->SetAllSendPackets(data);
}
