#include <common/Common.h>

// Macros
#ifndef __INTELLISENSE__
    #define static_assert(cond) __static_assert((cond), #cond)
    #define size_assert(type, size) static_assert(sizeof(type) == (size))
#else
    #define size_assert(type, size)
#endif
