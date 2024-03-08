#include <common/Common.hpp>
#include <game/ui/LayoutUIControl.hpp>
#include <game/ui/UIControlTimer.hpp>

class CountdownTimerControl : public LayoutUIControl {
public:
    virtual ~CountdownTimerControl();

    virtual void initSelf();
    virtual void calcSelf();

    virtual const TypeInfo* getTypeInfo() const;
    virtual const char* getTypeName() const;

    UIControlTimer* timer;
    bool _178;
};
size_assert(CountdownTimerControl, 0x17C);
