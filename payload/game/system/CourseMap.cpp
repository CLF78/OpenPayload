#include <common/Common.hpp>
#include <game/system/CourseMap.hpp>

/////////////////////////////
// Invalid KMP Point Fixes //
/////////////////////////////

// Prevent invalid item points from crashing the game
const MapdataItemPoint* CourseMap::getDummyItemPoint() {
    static const MapdataItemPoint::SData dummyPointData = {{0.0f, 0.0f, 0.0f}, 1.0f, {0, 0}};
    static const MapdataItemPoint dummyPoint = {(MapdataItemPoint::SData*)&dummyPointData };

    return &dummyPoint;
}

// CourseMap::getItemPoint() override
// Prevent invalid item points from crashing the game
kmBranchDefCpp(0x80514D3C, NULL, const MapdataItemPoint*, CourseMap* self, u32 id) {
    if (!self->mpItemPoint || id >= self->mpItemPoint->numEntries)
        return CourseMap::getDummyItemPoint();

    return self->mpItemPoint->entries[id];
}

// Prevent invalid cannon points from crashing the game
const MapdataCannonPoint* CourseMap::getDummyCannonPoint() {
    static const MapdataCannonPoint::SData dummyPointData = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0, 0};
    static const MapdataCannonPoint dummyPoint = {(MapdataCannonPoint::SData*)&dummyPointData};

    return &dummyPoint;
}

// CourseMap::getCannonPoint() override
// Prevent invalid cannon points from crashing the game
kmBranchDefCpp(0x80518AE0, NULL, const MapdataCannonPoint*, CourseMap* self, u32 id) {
    if (!self->mpCannonPoint || id >= self->mpCannonPoint->numEntries)
        return CourseMap::getDummyCannonPoint();

    return self->mpCannonPoint->entries[id];
}
