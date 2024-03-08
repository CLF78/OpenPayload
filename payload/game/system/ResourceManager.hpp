#include <common/Common.hpp>
#include <egg/core/eggTaskThread.hpp>
#include <game/system/MultiDvdArchive.hpp>

class ResourceManager {
public:

    class MenuKartArchive {
    public:
        virtual ~MenuKartArchive();

        EGG::Heap* archiveHeap;
        EGG::Heap* fileHeap;

        u32 state;
        u32 character;
        u32 modelType;
    };
    size_assert(MenuKartArchive, 0x18);

    struct JobContext {

        enum JobType {
            GENERIC,
            UI,
            TRACK,
            MISSION,
            COMPETITION,
            KART,
            MII,
        };

        MultiDvdArchive* multiArchive;
        DvdArchive* archive;
        u32 resourceID;
        char filename[0x40];

        EGG::Heap *archiveHeap;
        EGG::Heap *fileHeap;
    };
    size_assert(JobContext, 0x54);

    virtual ~ResourceManager();

    void* getFile(int source, const char* path, size_t* size);
    void process();
    static void doLoadTask(int jobContext);

    MultiDvdArchive* loadMission(u32 courseId, u32 missionNum, EGG::Heap* heap, bool isSplitScreen);

    MultiDvdArchive** multis;

    MultiDvdArchive kartArchives[12];
    MultiDvdArchive kartArchives2[12];
    DvdArchive variousArchives[4];

    JobContext jobContexts[7];
    EGG::TaskThread* taskThread;
    u8 unused[0x24]; // previously CourseCache

    MenuKartArchive allKartArchives[4];
    bool isGlobeLoadingBusy;
    bool _60D;

    EGG::Heap* menuManagerHeap;
    EGG::Heap* globeHeap;

    bool requestPending;
    bool requestsEnabled;

    static const char* courseNames[67];
    static ResourceManager* instance;
};
size_assert(ResourceManager, 0x61C);
