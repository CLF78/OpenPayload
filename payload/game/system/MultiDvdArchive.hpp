#include <common/Common.hpp>
#include <game/system/DvdArchive.hpp>

class MultiDvdArchive {
public:
    enum Type {
        COMMON,
        COURSE,
        MENU,
        FONT,
        EARTH,
        MIIBODY,
        DRIVER,
        DEMO,
        BACKMODEL,
    };

    enum KindFlag {
        SUFFIX_ONLY = BIT_FLAG(-1),
        FULL_NAME   = BIT_FLAG(0),
        CACHED      = BIT_FLAG(2),
    };

    virtual ~MultiDvdArchive();
    virtual void init();

    bool isLoaded();
    bool exists(const char* path);

    DvdArchive* archives;
    u16 archiveCount;
    u32* fileSizes;
    char** suffixes;
    void** fileStarts;
    int* kinds;

    static MultiDvdArchive* create(int type);
};
size_assert(MultiDvdArchive, 0x1C);
