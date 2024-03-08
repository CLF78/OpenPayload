#include <common/Common.hpp>
#include <egg/core/eggHeap.hpp>
#include <nw4r/ut/utList.hpp>

class ParameterFile {
public:
    virtual ~ParameterFile();
    virtual void read(EGG::Heap* heap);

    s32 vf_10();
    virtual void vf_14();
    virtual void vf_18();
    virtual void vf_1c();

    nw4r::ut::List strings;
    u32 totalAllocated;
    const char* path;
    u32 _18;
};
size_assert(ParameterFile, 0x1C);
