#include <common/Common.hpp>
#include <game/system/SaveManager.hpp>

//////////////////////////
// Wiimmfi Data Sharing //
//////////////////////////

// When revoking consent to data sharing, toggle the Wiimmfi-specific data sharing bit so the DNS method
// can ask the player to consent to data sharing again
kmBranchDefCpp(0x80600D10, 0x80600D78, void) {
    SaveManager::instance->rawSaveCopy->globalData.settings &= ~RawSave::GlobalData::WIIMMFI_DATA_SHARING;
}
