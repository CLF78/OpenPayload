#include <common/Common.hpp>
#include <egg/core/eggHeap.hpp>

void* operator new(size_t size, void* buffer);
void* operator new(size_t size, int align);
void* operator new(size_t size, EGG::Heap* heap, int align);

void* operator new[](size_t size, void* buffer);
void* operator new[](size_t size, int align);
void* operator new[](size_t size, EGG::Heap* heap, int align);
