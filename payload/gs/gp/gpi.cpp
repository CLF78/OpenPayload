#include <common/Common.hpp>
#include <gs/gp/gp.h>
#include <gs/gp/gpiBuddy.h>
#include <platform/string.h>
#include <wiimmfi/Kick.hpp>

//////////////////////////
// Wiimmfi Kick Support //
//////////////////////////

// gpiProcessConnectionManager() patch
// Parse Wiimmfi kick messages
// Credits: Wiimmfi
kmCallDefCpp(0x800FCEE8, int, GPConnection conn, char* data) {

    // Reproduce skipped code
    if (strstartw(data, "\\bsi\\"))
        return gpiProcessRecvBuddyStatusInfo(conn, data);

    // Call Wiimmfi code
    return Wiimmfi::Kick::ParseKickMessage(conn, data);
}

// Glue code
kmBranch(0x800FCEC8, 0x800FCEE0);
