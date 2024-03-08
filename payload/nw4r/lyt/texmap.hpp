#include <common/Common.hpp>

namespace nw4r {
namespace lyt {

class TexMap {
public:
    u8 unk[0x1C];

    void ReplaceImage(void* image, u32 id); // Actually TPLDescriptor* but i cannot be arsed
};

} // namespace lyt
} // namespace nw4r
