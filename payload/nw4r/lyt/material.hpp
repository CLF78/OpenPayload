#include <common/Common.hpp>
#include <nw4r/lyt/texmap.hpp>

namespace nw4r {
namespace lyt {

class Material {
public:
    u8 unk[0x3C];
    u32 flags;

    TexMap* GetTexMapAry();
};

} // namespace lyt
} // namespace nw4r
