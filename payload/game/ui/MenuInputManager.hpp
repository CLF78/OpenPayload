#include <common/Common.hpp>
#include <game/ui/TypeInfo.hpp>

class MenuInputManager {
public:
    enum InputType {
        FORWARD_PRESS,
        BACK_PRESS,
        START_PRESS,
        UP_PRESS,
        DOWN_PRESS,
        LEFT_PRESS,
        RIGHT_PRESS,
        UNK_7,
        UNK_8, // Home button maybe?
        INPUT_COUNT,
    };

    virtual TypeInfo* getTypeInfo() const;
    virtual ~MenuInputManager();
    virtual void init(u32 playerFlags, bool isMultiPlayer);
    virtual void vf_14();
    virtual void vf_18();
    virtual void vf_1c();
    virtual void onActivate(bool isMultiPlayer);
    virtual void vf_24();
    virtual void vf_28();
    virtual void vf_2c();
    virtual void vf_30();
    virtual void vf_34();

    u32 playerFlags;
    u32 playerEnabledFlags; // (1 << player) to enable inputs for player X
    bool inaccessible;
    bool isMultiPlayer;
    u8 _E;
};
size_assert(MenuInputManager, 0x10);
