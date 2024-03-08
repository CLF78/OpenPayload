#include <common/Common.hpp>

// Generic functions meant for mods to override
namespace ModSupport {

    // Process custom match commands
    // Return true if the custom function recognized the custom command
    bool ProcessRecvMatchCommand(u8 cmd, int profileId, u32 publicIp, u16 publicPort, void* cmdData, int dataLen);

    // Return true if Ultra UnCut should be enabled
    // It's recommended to turn it on for Worldwide matches
    bool AreUltraShortcutsEnabled();

    // Return the race time limit, in milliseconds
    u32 GetOnlineTimeLimit();

    // Return a custom UPNP port if a specific one is requested, else 0 to let Wiimmfi derive it from
    // the console serial number
    u16 GetCustomUPNPPort();

    // Allows relaxing the checks for valid data (e.g custom packets)
    // Return true if the packet section is valid (see RKNetRacePacketHeader.hpp for the section index)
    bool IsPacketSectionDataValid(int section, u8* sectionData, u32 sectionDataLen);

    // Gets the Online VS region
    u16 GetVSRegion();

    // Gets the Online Battle region
    u16 GetBTRegion();

} // namespace ModSupport
