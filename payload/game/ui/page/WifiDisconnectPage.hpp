#include <common/Common.hpp>
#include <game/net/WifiDisconnectInfo.hpp>
#include <game/ui/LayoutUIControl.hpp>
#include <game/ui/Page.hpp>
#include <game/ui/PageInputManager.hpp>

class WifiDisconnectPage : public Page {
public:
    PageInputManager inputManager;
    WifiDisconnectInfo disconnectInfo;
    LayoutUIControl messageBox;
    LayoutUIControl okButton;
    InputHandler0<WifiDisconnectPage, void> onBtnSelect;
};
size_assert(WifiDisconnectPage, 0x48C);
