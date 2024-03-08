#include <common/Common.hpp>
#include <game/ui/MenuInputManager.hpp>

class ButtonInfo { 
public:
    virtual ~ButtonInfo();

    u32 pressTimes[MenuInputManager::INPUT_COUNT];
    bool buttonHeld[MenuInputManager::INPUT_COUNT];
};
size_assert(ButtonInfo, 0x34);
