#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSModuleInfo OSModuleInfo;

typedef struct {
    OSModuleInfo* next;
    OSModuleInfo* prev;
} OSModuleLink;

typedef struct {
    OSModuleInfo* head;
    OSModuleInfo* tail;
} OSModuleQueue;

struct OSModuleInfo {
    u32 id;
    OSModuleLink link;
    u32 numSections;
    u32 sectionInfoOffset;
    u32 nameOffset;
    u32 nameSize;
    u32 version;
};

#ifdef __cplusplus
}
#endif
