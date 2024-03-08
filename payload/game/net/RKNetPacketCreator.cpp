#include <common/Common.hpp>

//////////////////
// Game Lag Fix //
//////////////////

// RKNetPacketCreator::updateAsRacer() patch
// Disable processing of lag frames to fix matrix slowdown and delays caused by slower Dolphin players
// Credits: Wiimmfi
kmWrite32(0x80654400, 0x60000000);
