#include <common/Common.hpp>
#include <game/net/RKNetController.hpp>
#include <game/ui/SectionManager.hpp>
#include <game/ui/page/WifiDisconnectPage.hpp>

/////////////////////////////
// Improved Error Messages //
/////////////////////////////

// Inline helper
inline bool IsErrorInRange(u32 errorCode, u32 min, u32 max) {
    return errorCode >= min && errorCode < max;
}

// Customize the error message based on the error code
u32 GetErrorMessage(u32 errorCode, MessageInfo* extraInfo) {

    // 20XXX - Nintendo NASWII error codes
    if (IsErrorInRange(errorCode, 20000, 21000)) {
        switch(errorCode) {

            // Can't connect to the internet
            case 20100:
                return 4601;

            // WFC shutdown message, can only appear if domain patches were applied incorrectly
            case 20110:
                return 4602;

            // Let other errors fall back to a generic message
            default:
                return 4603;
        }

    // 23XXX - Wiimmfi NASWII error codes
    } else if (IsErrorInRange(errorCode, 23000, 24000)) {
        switch(errorCode) {

            // 1 hour before activation
            case 23801:
                return 4605;

            // XX hours before activation
            case 23802 ... 23879:
                extraInfo->intVals[1] = errorCode - 23800;
                return 4604;

            // 1 day before activation
            case 23881:
                return 4609;

            // X days before activation
            case 23882 ... 23887:
                extraInfo->intVals[1] = errorCode - 23880;
                return 4606;

            // Console registered but needs activation
            case 23899:
                return 4610;

            // Server under maintenance
            case 23901:
                return 4611;

            // Server under heavy traffic
            case 23902:
                return 4612;

            // Profile creation disabled
            case 23903:
                return 4613;

            // Outdated patches (may happen in the future)
            case 23904 ... 23905:
            case 23951 ... 23953:
                return 4614;

            // Banned profile (imported savegame most likely)
            case 23910:
            case 23912:
                return 4615;

            // Profile creation denied
            case 23911:
                return 4616;

            // Console creation denied
            case 23913:
                return 4617;

            // Console banned
            case 23914:
                return 4618;

            // NAND not imported
            case 23915:
            case 23918:
                return 4619;

            // Proxies not allowed
            case 23916:
                return 4620;

            // User banned
            case 23917:
                return 4621;

            // Profile not created on Wiimmfi
            case 23919:
                return 4622;

            // Offensive or invalid Mii
            case 23927 ... 23928:
                return 4623;

            // Various patching errors
            case 23931 ... 23935:
            case 23971 ... 23973:
                return 4602;

            // Let other errors fall back to a generic message
            default:
                return 4603;
        }

    // 29XXX - NAND Errors
    } else if (IsErrorInRange(errorCode, 29000, 30000)) {
        switch(errorCode) {

            // NAND full
            case 29000:
                return 4607;

            // NAND damaged
            case 29001:
                return 4608;

            // Let other errors fall back to a generic message
            default:
                return 4639;
        }

    // 31XXX - DLS1 Errors
    } else if (IsErrorInRange(errorCode, 31000, 32000))
        return 4624;

    // 33XXX - Profanity Check Errors
    else if (IsErrorInRange(errorCode, 33000, 34000))
        return 4626;

    // 5XXXX - Network Connection Errors
    else if (IsErrorInRange(errorCode, 50000, 60000)) {
        switch (errorCode) {

            // No internet connection configured
            case 50200 ... 50299:
                return 4627;

            // Cannot connect to LAN
            case 50400 ... 50499:
            case 51400 ... 51499:
                return 4628;

            // Cannot connect to access point
            case 51000 ... 51099:
            case 51300 ... 51399:
                return 4629;

            // DHCP error or IP address conflict
            case 52000 ... 52099:
            case 52700 ... 52799:
                return 4630;

            // DNS error
            case 52100 ... 52199:
                return 4631;

            // Proxy configuration error
            case 52400 ... 52599:
                return 4632;

            // Unstable connection
            case 54000 ... 54099:
                return 4633;

            // Fall back to a generic error message
            default:
                return 4601;
        }

    // 6XXXX - Network Errors (Login State)
    } else if (IsErrorInRange(errorCode, 60000, 70000)) {
        switch (errorCode) {

            // Error 60000 cannot appear unless the patch was removed
            case 60000:
                return 4602;

            // Fall back to a generic error message
            default:
                return 4634;
        }

    // 7XXXX - Network Errors (Friend Roster Synchronization State)
    } else if (IsErrorInRange(errorCode, 70000, 80000)) {
        switch (errorCode) {

            // Possible kick or ban
            case 71010:
                return 4638;

            // Fall back to a generic error message
            default:
                return 4635;
        }

    // 8XXXX - Network Errors (Matchmaking State)
    } else if (IsErrorInRange(errorCode, 80000, 90000)) {
        switch (errorCode) {

            // Possible kick or ban
            case 81010:
                return 4638;

            // Bad connection
            case 86420:
                return 4640;

            // Fall back to a generic error message
            default:
                return 4636;
        }

    // 9XXXX - Network Errors (Other Stage)
    } else if (IsErrorInRange(errorCode, 90000, 100000)) {
        switch (errorCode) {

            // Possible kick or ban
            case 91010:
                return 4638;

            // Fall back to a generic error message
            default:
                return 4637;
        }

    // 1XXXXX - WiiConnect24 Errors
    } else if (errorCode >= 100000)
        return 4600;

    // Fallback to all the above
    return 4625;
}

// WifiDisconnectedPage::onActivate() override
// Display the error code in more cases and make the error messages more descriptive
kmPointerDefCpp(0x808BFB74, void, WifiDisconnectPage* self) {

    // Display the OK button by default
    self->okButton.hidden = false;

    // Get the section
    Section* section = SectionManager::instance->curSection;

    // If the disconnection was triggered by the game, there are no error codes to display
    if (section->sectionID == Section::DC_WITHOUT_ERROR_CODE) {
        section->shutdownNet();
        self->messageBox.setText(4018, nullptr);
        return;
    }

    // Get the disconnection info
    if (section->sectionID == Section::DC_WITH_ERROR_CODE || section->sectionID == Section::UNK_98) {
        self->disconnectInfo = SectionManager::instance->globalContext->disconnectInfo;
        SectionManager::instance->globalContext->disconnectInfo.reset();
    } else {
        self->disconnectInfo = RKNetController::instance->getWifiDisconnectInfo();
    }

    // Setup message info with category and error code (not used by every message)
    u32 disconnectCategory = self->disconnectInfo.errorCategory;
    MessageInfo msgInfo;
    msgInfo.intVals[0] = self->disconnectInfo.errorCode;

    // Various errors, display a different message depending on the error code
    if (disconnectCategory == WifiDisconnectInfo::ERROR_WITH_CODE) {
        u32 errorMsg = GetErrorMessage(self->disconnectInfo.errorCode, &msgInfo);
        self->messageBox.setText(errorMsg, &msgInfo);
        section->shutdownNet();

    // Mii name detected as offensive, use the dedicated message (no error codes available)
    } else if (disconnectCategory == WifiDisconnectInfo::ERROR_OFFENSIVE_MII) {
        self->messageBox.setText(4016, nullptr);
        section->shutdownNet();

    // Generic error, unsure of use cases
    } else if (disconnectCategory == WifiDisconnectInfo::ERROR_GENERIC) {
        self->messageBox.setText(2072, nullptr);
        section->shutdownNet();

    // There was a fatal error, prevent returning to the main menu and display the error code
    // TODO allow restarting the game instead of disabling the button?
    } else if (disconnectCategory == WifiDisconnectInfo::ERROR_UNRECOVERABLE) {
        self->messageBox.setText(2052, &msgInfo);
        self->okButton.hidden = true;
        self->inputManager.playerEnabledFlags = 0;
    }
}
