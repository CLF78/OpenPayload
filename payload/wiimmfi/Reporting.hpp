#include <common/Common.hpp>
#include <game/net/packet/RKNetRoomPacket.hpp>

// Contains all Wiimmfi telemetry
namespace Wiimmfi {
namespace Reporting {

    ///////////////
    // Constants //
    ///////////////

    // Constants for formatting SHA1 hashes
    static const int HASH_STRING_SIZE = sizeof("1234567812345678123456781234567812345678");
    static const char HASH_STRING_FMT[] = "%08x%08x%08x%08x%08x";

    ///////////////
    // Functions //
    ///////////////

    // Reports the AID to PID map when it changes
    void ReportAIDPIDMap();

    // Reports the battle results - UNUSED
    // void ReportBattleResults();

    // Reports various Common.szs subfiles that can be modified for cheating
    void ReportCommonSubfiles();

    // Reports the connection matrix
    void ReportConnectionMatrix(u32 aidsConnectedToMe);

    // Reports various course subfiles for possible track identification/cheat detection
    void ReportCourseSubfiles();

    // Reports the race finish time of the given local player
    void ReportFinishTime(u8 playerIdx);

    // Reports the frame count at certain intervals
    void ReportFrameCount(u32 frameCount);

    // Reports a room start
    void ReportFriendRoomStart(RKNetROOMPacket* packet);

    // Reports the AID of the host when it changes
    void ReportHostSlotChange();

    // Reports a match state change, if it has happened
    void ReportMatchStateChange();

    // Reports the race stage
    void ReportRaceStage(u32 stage);

    // Reports a region change
    void ReportRegionChange();

    // Reports information extracted from the SELECT packet
    void ReportSELECTInfo();

    // Reports host disconnections
    void ReportServerDown(u32 cmd, u32 pid, u32* data);

    // Reports the console signature and certificate
    void ReportSignatureAndCert();

    // Reports NATNEG suspend updates
    void ReportSuspendUpdate();

    // Reports the given track SHA1 hash
    void ReportTrackHash(u32* hash, u8 courseId);

    ///////////////
    // Variables //
    ///////////////

    // The next frame when a frame report will be sent
    extern u32 sTargetFrameCount;

} // namespace Reporting
} // namespace Wiimmfi
