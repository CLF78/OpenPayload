#include <common/Common.hpp>
#include <game/ui/Page.hpp>
#include <game/ui/page/MessagePopupPage.hpp>
#include <wiimmfi/Auth.hpp>
#include <wiimmfi/Status.hpp>

////////////////////////////////
// Wiimmfi Console Assignment //
////////////////////////////////

// WifiMenuPage::beforeCalc() override
// Display the Wiimmfi console assignment message if available
// Credits: Wiimmfi
kmPointerDefCpp(0x808BFF8C, void, Page* self) {

    // Check if a message is available, if not bail
    if (!Wiimmfi::Auth::sConsoleAssignMessage)
        return;

    // Get the message popup page, if not available bail
    MessagePopupPage* page = MessagePopupPage::getPage();
    if (!page) return;

    // Inform the server we have seen the message
    Wiimmfi::Status::SendMessage("message", "type=server");

    // Display the message
    MessageInfo msgInfo;
    msgInfo.strings[0] = Wiimmfi::Auth::sConsoleAssignMessage;
    page->setWindowMessage(6602, &msgInfo);

    // Display the page and delete the pointer so this doesn't run again next frame
    self->addPage(Page::MESSAGE_POPUP, Page::ANIM_NEXT);
    Wiimmfi::Auth::sConsoleAssignMessage = nullptr;
}
