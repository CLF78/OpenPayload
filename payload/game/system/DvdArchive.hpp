#include <common/Common.hpp>
#include <egg/core/eggHeap.hpp>

class DvdArchive {
public:

    enum State {
        CLEARED,
        UNK_1,
        RIPPED,
        DECOMPRESSED,
        MOUNTED,
        UNK_5,
    };

    virtual ~DvdArchive();

    void* getFile(const char* path, u32* size);

    void* archive; // actually EGG::Archive
    void* archiveBuffer;
    u32 archiveSize;
    EGG::Heap* archiveHeap;
    void* fileBuffer;
    u32 fileSize;
    EGG::Heap* fileHeap;
    u32 state;
};
size_assert(DvdArchive, 0x24);
