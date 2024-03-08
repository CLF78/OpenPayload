#include <common/Common.hpp>
#include <game/ui/ButtonInfo.hpp>
#include <game/ui/InputHandler.hpp>
#include <game/ui/LayoutUIControl.hpp>
#include <game/ui/MenuInputManager.hpp>

class PageInputManager : public MenuInputManager {
public:
    InputHandler2<LayoutUIControl, void, u32, u32>* handlers[9];
    bool isTriggered[INPUT_COUNT];
    ButtonInfo buttoninfoArray[5];
};
size_assert(PageInputManager, 0x144);
