#include <common/Common.hpp>
#include <game/gfx/AnmHolder.hpp>

////////////////////
// Game Bug Fixes //
////////////////////

// Prevent Thwomps from crashing the game when they are hit before they land the first time
// Credits: MrBean35000vr
kmCallDefCpp(0x80760A88, float, AnmHolder* anm) {

    // Get animation frame count, otherwise a dummy value
    return (anm != nullptr) ? anm->GetFrameCount() : 0.0f;
}

// Glue code
// kmBranchDefCpp cannot be used here due to compiler optimizations
kmBranch(0x80760A8C, 0x80760A98);
