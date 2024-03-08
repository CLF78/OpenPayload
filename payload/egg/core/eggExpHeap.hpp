#include <egg/core/eggHeap.hpp>

namespace EGG {

class ExpHeap : public Heap {
public:

    struct GroupSizeRecord {
        u32 entries[256];
    };

    virtual ~ExpHeap();
    virtual int getHeapKind();
    virtual void initAllocator(Allocator* allocator, s32 alignment);
    virtual void* alloc(size_t size, s32 alignment);
    virtual void free(void* buffer);
    virtual void destroy();
    virtual u32 resizeForMBlock(void* buffer, u32 newSize);
    virtual u32 getAllocatableSize(s32 alignment);
    virtual u32 adjust();
};
size_assert(ExpHeap, sizeof(Heap));

} // namespace EGG
