#include <common/Common.hpp>

struct TypeInfo {
    TypeInfo* base;
};
size_assert(TypeInfo, 0x4);
