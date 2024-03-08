#include <common/Common.hpp>
#include <revolution/mem/allocator.h>

namespace EGG {

class Heap;

class Allocator : public MEMAllocator {
public:
    virtual ~Allocator();
    virtual void* alloc(u32 size);
    virtual void free(void* buffer);

    Heap* heap;
    s32 alignment;
};

} // namespace EGG
