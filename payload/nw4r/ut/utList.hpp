#include <common/Common.hpp>

namespace nw4r {
namespace ut {

typedef struct {
    void* prev;
    void* next;
} Link;

typedef struct {
    void* head;
    void* tail;
    u16 count;
    u16 offset;
} List;

typedef struct {
    u32 count;
    Link node;
} LinkListImpl;

} // namespace ut
} // namespace nw4r
