#include <common/Common.hpp>
#include <egg/core/eggAllocator.hpp>
#include <egg/core/eggDisposer.hpp>
#include <nw4r/ut/utList.hpp>
#include <revolution/mem/heapCommon.h>

namespace EGG {

class Heap : public Disposer {
    public:
        virtual ~Heap();
        virtual int getKind() = 0;
        virtual void initAllocator(Allocator* allocator, s32 alignment) = 0;
        virtual void* alloc(size_t size, s32 alignment) = 0;
        virtual void free(void* buffer) = 0;
        virtual void destroy() = 0;
        virtual u32 resizeForMBlock(void* buffer, u32 newSize) = 0;
        virtual u32 getAllocatableSize(s32 alignment) = 0;

        MEMiHeapHead* mHeapHandle;
        void* mParentBlock;
        Heap* mParentHeap;
        u16 mFlag;
        // 2 bytes padding

        nw4r::ut::Link mLink;
        nw4r::ut::List mChildren;
        const char* mName;

        static void* alloc(size_t size, int align, Heap* heap);
        static void free(void* buffer, Heap* heap);
};
size_assert(Heap, 0x38);

} // namespace EGG
