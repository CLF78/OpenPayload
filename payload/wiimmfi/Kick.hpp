#include <common/Common.hpp>
#include <gs/gp/gp.h>

namespace Wiimmfi {
namespace Kick {

    ///////////////
    // Constants //
    ///////////////

    // The possible kick types
    enum Type {
        NONE,
        EVERYONE,
        SELF,
        END_RACE,
        SPECIFIC_PLAYER,
    };

    // The server message for kicking and pid to kick
    static const char KICK_MSG[] = "\\wiimmfi\\kick";
    static const char KICK_MSG_PARAM_PID[] = "\\kickpid\\";

    ///////////////
    // Functions //
    ///////////////

    // Schedules a kick for the given AID
    void ScheduleForAID(int aid);

    // Schedules a kick for the AIDs in the given bitmap
    void ScheduleForAIDs(u32 aidMap);

    // Schedules a kick for everyone in the room
    void ScheduleForEveryone();

    // Runs the kicking task
    void CalcKick();

    // Parses a kick message received from the server
    int ParseKickMessage(GPConnection conn, char* data);

    ///////////////
    // Variables //
    ///////////////

    // If the race should be stopped immediately (used by kick type END_RACE)
    extern bool sMustEndRace;

} // namespace Kick
} // namespace Wiimmfi
