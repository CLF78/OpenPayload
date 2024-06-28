#include <common/Common.hpp>
#include <game/system/CourseMap.hpp>

/////////////////////////////
// Invalid KMP Point Fixes //
/////////////////////////////

// Restore original item point behaviour to prevent lag in Battle Mode
kmCallDefCpp(0x805845D8, const MapdataItemPoint*, CourseMap* self, u32 id) {

    // Get item point
    const MapdataItemPoint* point = self->getItemPoint(id);

    // If the function returned the dummy point, restore original behaviour and return null
    if (point == CourseMap::getDummyItemPoint())
        return nullptr;

    return point;
}
