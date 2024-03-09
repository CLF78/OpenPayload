#include <common/Common.hpp>
#include <dwc/dwc_match.h>
#include <game/net/RKNetController.hpp>
#include <game/net/RKNetSelectHandler.hpp>
#include <game/race/RaceGlobals.hpp>
#include <game/system/RaceManager.hpp>
#include <game/ui/page/FriendRoomJoinPage.hpp>
#include <nw4r/ut/Lock.hpp>
#include <revolution/vi.h>
#include <revolutionex/net/NETDigest.h>
#include <wiimmfi/Delay.hpp>
#include <wiimmfi/Kick.hpp>
#include <wiimmfi/Natneg.hpp>
#include <wiimmfi/Reporting.hpp>
#include <wiimmfi/Security.hpp>
#include <wiimmfi/Status.hpp>

/////////////////
// Fast NATNEG //
/////////////////

// RKNetController::mainNetworkLoop() patch
// Update NATNEG
// Credits: Wiimmfi
// Q: Can we move this to the main Wiimmfi network loop?
kmCallDefCpp(0x80657990, void, RKNetController* self) {

    // Original call
    self->updateSubsAndVr();

    // Update Wiimmfi NATNEG
    // Since we're in a matching state, force the value to 0
    Wiimmfi::Natneg::CalcTimers(false);
}

/////////////
// RCE Fix //
/////////////

// RKNet_UserRecvCallback() patch
// Validate incoming player data to prevent remote code execution exploits
// Credits: WiiLink24, Wiimmfi
kmBranchDefCpp(0x80658610, NULL, void, RKNetController* self, u32 aid, RKNetRACEPacketHeader* data, u32 dataLength) {

    // Bail if the packet doesn't even include a full header
    if (dataLength < sizeof(RKNetRACEPacketHeader))
        return;

    // Verify the checksum
    // The game already does this later, but we shouldn't disconnect a player because a packet got corrupted
    u32 savedChecksum = data->checksum;
    data->checksum = 0;
    u32 realChecksum = NETCalcCRC32(data, dataLength);
    data->checksum = savedChecksum;
    if (realChecksum != savedChecksum) {
        DEBUG_REPORT("[RKNET] Detected corrupted packet from aid %d\n", aid)
        return;
    }

    // If the packet is valid, process it
    // Else kick the aid who sent it
    if (Wiimmfi::Security::ValidateRACEPacket(aid, data, dataLength))
        self->processRacePacket(aid, data, dataLength);
    else {
        nw4r::ut::AutoInterruptLock lock;
        DEBUG_REPORT("[RKNET] Detected malicious packet from aid %d\n", aid)

        // Do not kick players if we're not host
        if (self->isPlayerHost())
            Wiimmfi::Kick::ScheduleForAID(aid);

        // Warn the user if possible
        FriendRoomJoinPage* page = FriendRoomJoinPage::getPage();
        if (page) page->forceConnectionError();
    }
}

/////////////////////////////////
// Wiimmfi Telemetry / Various //
/////////////////////////////////

// RKNetController::mainNetworkLoop() patch
// Main Wiimmfi update function
// Credits: Wiimmfi
kmCallDefCpp(0x806579B0, void) {

    // Only run the tasks if we are online
    if (stpMatchCnt) {
        nw4r::ut::AutoInterruptLock lock;
        Wiimmfi::Kick::CalcKick();
        Wiimmfi::Reporting::ReportMatchStateChange();
        Wiimmfi::Natneg::StopNATNEGAfterTime();
        Wiimmfi::Reporting::ReportSuspendUpdate();
        Wiimmfi::Reporting::ReportAIDPIDMap();
        Wiimmfi::Reporting::ReportHostSlotChange();
        Wiimmfi::Reporting::ReportRegionChange();

        // Only run race tasks if we are in an online race
        if (RaceGlobals::isOnlineRace && RaceManager::instance != nullptr) {
            Wiimmfi::Reporting::ReportFrameCount(RaceManager::instance->frameCounter);
            Wiimmfi::Delay::Calc(RaceManager::instance->frameCounter);
        }

        // Only run SELECT-tasks if the handler exists
        if (RKNetSELECTHandler::instance)
            Wiimmfi::Reporting::ReportSELECTInfo();
    }

    // Original call
    VIWaitForRetrace();
}
