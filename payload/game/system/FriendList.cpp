#include <common/Common.hpp>

///////////////////////////////////
// Invalid Profile ID Antifreeze //
///////////////////////////////////

// Prevent invalid profile identifiers from crashing the game
// Credits: MrBean35000vr
kmBranch(0x805D2EF8, 0x805D2EBC);
kmBranch(0x805D2F00, 0x805D2EBC);
