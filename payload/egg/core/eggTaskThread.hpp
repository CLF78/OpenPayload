#include <common/Common.hpp>

namespace EGG {

class TaskThread {
public:
    bool request(Func func, s32 arg0, s32 arg1); 
};

} // namespace EGG
