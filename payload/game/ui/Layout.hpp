#include <common/Common.hpp>
#include <nw4r/lyt/pane.hpp>

class Layout {
public:
    u8 _00[0x28];

    nw4r::lyt::Pane* getPaneByName(const char* name);
};
size_assert(Layout, 0x28);

class MainLayout : public Layout {
public:
    u8 _28[0x9c - 0x28];
};
size_assert(MainLayout, 0x9C);

class PictureSourceLayout : public Layout {
public:
    u8 _28[0xb0 - 0x28];
};
size_assert(PictureSourceLayout, 0xB0);
