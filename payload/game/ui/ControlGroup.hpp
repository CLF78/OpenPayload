#include <common/Common.hpp>

class Page;
class UIControl;

class ControlGroup {
public:
    UIControl** data;
    UIControl** dataSorted; // By draw order
    UIControl* parent;
    Page* page;
    s32 dataSize;
};
size_assert(ControlGroup, 0x14);
