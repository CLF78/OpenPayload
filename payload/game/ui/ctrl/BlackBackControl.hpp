#include <common/Common.hpp>
#include <game/ui/LayoutUIControl.hpp>

class BlackBackControl : public LayoutUIControl {
public:
    virtual ~BlackBackControl();

    virtual void solveAnim(Element* element, float frame);

    virtual const TypeInfo* getTypeInfo() const;
    virtual const char* getTypeName() const;
};
size_assert(BlackBackControl, 0x174);
