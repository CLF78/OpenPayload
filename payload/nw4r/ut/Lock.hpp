#include <common/Common.hpp>
#include <revolution/os/OS.h>

namespace nw4r {
namespace ut {

class AutoInterruptLock {
public:

    AutoInterruptLock() : mOldState(OSDisableInterrupts()) {}
    ~AutoInterruptLock() { OSRestoreInterrupts(mOldState); }

    BOOL mOldState;
};

} // namespace ut
} // namespace nw4r
