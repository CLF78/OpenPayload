#include <common/Common.hpp>
#include <game/ui/InputHandler.hpp>
#include <game/ui/Page.hpp>
#include <game/ui/PageInputManager.hpp>

class MessagePage : public Page {
public:
    virtual ~MessagePage();

    virtual void onInit();
    virtual void onActivate();
    virtual void onDeactivate();
    virtual void afterCalc();

    virtual TypeInfo* getTypeInfo() const;

    virtual void reset();
    virtual void setWindowMessage(u32 msgId, MessageInfo* msgInfo) = 0;
    virtual void process() = 0;

    PageInputManager inputManager;
    InputHandler0<MessagePage, void>* onPopupFront;
    InputHandler0<MessagePage, void> onFront;
    u32 playerFlags;
    u32 _1A4;
};
size_assert(MessagePage, 0x1A8);
