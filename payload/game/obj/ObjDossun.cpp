#include <common/Common.hpp>
#include <game/gfx/AnmHolder.hpp>

////////////////////
// Game Bug Fixes //
////////////////////

// Prevent Thwomps from crashing the game when they are hit before they land the first time
// Credits: MrBean35000vr
kmBranchDefCpp(0x80760A88, 0x80760A98, float, AnmHolder* anm) {

	// Get animation frame count, otherwise a dummy value
	return (anm != nullptr) ? anm->GetFrameCount() : 0.0f;
}
