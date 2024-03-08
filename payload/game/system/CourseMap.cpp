#include <common/Common.hpp>
#include <game/system/CourseMap.hpp>

/////////////////////////////
// Invalid KMP Point Fixes //
/////////////////////////////

// CourseMap::getItemPoint() override
// Prevent invalid item points from crashing the game
kmBranchDefCpp(0x80514D3C, NULL, const MapdataItemPoint*, CourseMap* self, u32 id) {

    static const MapdataItemPoint::SData dummyPointData = {{0.0f, 0.0f, 0.0f}, 1.0f, {0, 0}};
    static const MapdataItemPoint dummyPoint = {(MapdataItemPoint::SData*)&dummyPointData };

    if (!self->mpItemPoint || id >= self->mpItemPoint->numEntries)
        return &dummyPoint;

    return self->mpItemPoint->entries[id];
}

// CourseMap::getCannonPoint() override
// Prevent invalid cannon points from crashing the game
kmBranchDefCpp(0x80518AE0, NULL, const MapdataCannonPoint*, CourseMap* self, u32 id) {

    static const MapdataCannonPoint::SData dummyPointData = {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 0, 0};
    static const MapdataCannonPoint dummyPoint = {(MapdataCannonPoint::SData*)&dummyPointData};

    if (!self->mpCannonPoint || id >= self->mpCannonPoint->numEntries)
        return &dummyPoint;

    return self->mpCannonPoint->entries[id];
}
