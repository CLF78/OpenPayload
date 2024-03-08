#include <common/Common.hpp>
#include <game/ui/LayoutUIControl.hpp>
#include <game/ui/SectionManager.hpp>
#include <game/ui/ctrl/BlackBackControl.hpp>
#include <game/ui/page/MessagePage.hpp>

class MessagePopupPage : public MessagePage {
public:
    virtual ~MessagePopupPage();

    virtual void onInit();
    virtual void beforeInAnim();
    virtual void afterOutAnim();

    virtual TypeInfo* getTypeInfo() const;
    virtual void reset();
    virtual void setWindowMessage(u32 msgId, MessageInfo* msgInfo);
    virtual void process();

    static MessagePopupPage* getPage() {
        return (MessagePopupPage*)SectionManager::instance->curSection->pages[Page::MESSAGE_POPUP];
    }

    LayoutUIControl messageWindow;
    LayoutUIControl okButton;
    BlackBackControl blackBackControl;
};
size_assert(MessagePopupPage, 0x604);
