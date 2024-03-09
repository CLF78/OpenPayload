# OpenPayload
OpenPayload is an open-source reimplementation of the Wiimmfi payload for Mario Kart Wii.

## General Information
The Wiimmfi payload is a set of patches Wiimmfi provides to fix various game bugs and protect Mario Kart Wii players from malicious attacks. It is implemented as a binary blob that relies on security through obscurity, meaning it can easily interfere with more complex mods.

The reasons behind OpenPayload are the following:
- An open implementation allows for potential improvements and additional vetting on the patches;
- Not applying the patches at runtime means the game can connect to the server faster than it normally would;
- Features can be integrated by mods or left out entirely.

## Compilation
OpenPayload's code relies on the CodeWarrior compiler and the Kamek linker for hook insertion, therefore it can be easily imported into existing Kamek projects (or ported to other Wii code loaders).

Compilation instructions or compiled outputs will not be provided, as OpenPayload is meant to give more wiggle room to complex distributions rather than disrupt Wiimmfi's functionality.

## Implementation Details
OpenPayload is opinionated, meaning that some features are not reimplemented and some others are implemented differently, in order to follow proper programming practices and provide cleaner, less bloated code.

Major features that were not ported include:
- **Auto Reconnect**: Benefits of this feature are seemingly nonexistent, and the amount of code added is too much to justify the effort;
- **Cheat Reporting**: Since these are basically self-reports that generally do not lead to a ban (the reports themselves are not accessible to moderators), these hooks have been skipped. Once in-game reporting is *properly* implemented on both client and server side, porting will be considered;
- **Custom Error Messages**: Due to this feature being prone to breakage, it has been chosen to rely on an offline set of fixed error messages instead. The new version of the feature also displays the error code when the "disc error" occurs;
- **Frameskip**: The amount of code and its unreadability proved too much to handle. A skill issue, one could argue;
- **IOS Operation Protection**: This measure is extremely easy to bypass, offers no additional protection and only serves to make IOS access more annoying for mods.

### Mod Support
Some generic functions meant to showcase potential interoperation between mods and the payload have been defined in [ModSupport.hpp](/payload/ModSupport.hpp).

The message patches applied by the WSZST-based patcher have been converted to JSON5 and cleaned up, adding some missing translations and removing various translation error and broken escape sequences. They can be found in `assets`.

### Existing Hooks
The table below lists all the hooks used by the original Wiimmfi payload as of v96, their purpose, the reimplementation status and any changes that were made to the original code.

The legend is as follows:
- ✅: The code for this hook has been ported
- ☑️: The code for this hook has been ported, but the hook has been moved to a different address
- ⚠️: The code for this hook is currently being ported
- ⏭: The code for this hook will not be ported
- ❌: The code for this hook has not been ported yet

| **Hook Address(es)** | **Category** | **Purpose** | **Status** | **Code** | **Notes/Changes** |
|----------------------|--------------|-------------|:----------:|:--------:|-------------------|
| `0x800095C4`<br>`0x800095E4`<br>`0x800095F4` | Frameskip | Main Frameskip Function | ⏭ | N/A | Frameskip will not be implemented |
| `0x800CE220` | Security Fixes | Friend Status Data Buffer Overflow Fix | ✅ | [dwc_friend.cpp](/payload/dwc/dwc_friend.cpp) | N/A |
| `0x800CE7A4` | NATify Fixes | Update NATify | ✅ | [dwc_friend.cpp](/payload/dwc/dwc_friend.cpp)<br>[Natify.cpp](/payload/wiimmfi/Natify.cpp) | Changed disgusting runtime hook to a fixed hook |
| `0x800CECB0`<br>`0x800DEA18` | Auto Reconnect | Fix Friend Status Issues | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800CECBC`<br>`0x8065A0EC` | Auto Reconnect | DWC Stub Implementation | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800D01E4` | Auto Reconnect | Fix Error 61070 | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800D0598`<br>`0x800D059C`<br>`0x800D05A0` | Bug Fixes | Error 60000 Fix | ☑️<br>(Branch from `0x800D05A8` to `0x800D0610`) | [dwc_login.cpp](/payload/dwc/dwc_login.cpp) | Ensured the data type flag is properly cleared before setting it |
| `0x800D086C` | NATify Fixes | Start NATify | ✅ | [dwc_login.cpp](/payload/dwc/dwc_login.cpp)<br>[natneg.cpp](/payload/gs/natneg/natneg.cpp)<br>[Natify.cpp](/payload/wiimmfi/Natify.cpp) | <ul><li>Changed disgusting runtime hook to a fixed hook</li><li>Removed pointless call to `DetermineNatType`</li><li>Don't copy NATify data if the negotiation failed</li></ul> |
| `0x800D0DD4`<br>`0x800D0DE8` | NATNEG Fixes | Override Connected Callback | ☑️<br>(Moved to `0x800D0FE8`) | [dwc_main.cpp](/payload/dwc/dwc_main.cpp)<br>[Natneg.cpp](/payload/wiimmfi/Natneg.cpp) | What does this patch effectively do? |
| `0x800D13F4` | Auto Reconnect | Allow P2P While Offline | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800D1DDC`<br>`0x800D1F04`<br>`0x800D1FDC`<br>`0x800D2058` | Auto Reconnect | Don't Close P2P Connections When Disconnecting | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800D26DC`<br>`0x800D3050`<br>`0x800D3078`<br>`0x800D31A0`<br>`0x800D31BC`<br>`0x800D3624`<br>`0x800D3C38`<br>`0x800D3EA0`<br>`0x800E5680`<br>`0x80657648`<br>`0x8065764C`<br>`0x80658714`<br>`0x8065A970` | Auto Reconnect | N/A | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800D2884` | Port Binding | Use UPNP Port for NATNEG | ✅ | [dwc_main.cpp](/payload/dwc/dwc_main.cpp) | N/A |
| `0x800D28CC` | NATNEG Fixes | Override Connect Attempt Callback | ✅ | [dwc_main.cpp](/payload/dwc/dwc_main.cpp)<br>[Natneg.cpp](/payload/wiimmfi/Natneg.cpp) | What does this patch effectively do? |
| `0x800D31C4`<br>`0x80658F7C` | NATNEG Fixes | Reattempt NATNEG Multiple Times | ☑️<br>(Moved respectively to `0x800D3188` and `0x80657990`) | [dwc_main.cpp](/payload/dwc/dwc_main.cpp)<br>[RKNetController.cpp](/payload/game/net/RKNetController.cpp)<br>[Natneg.cpp](/payload/wiimmfi/Natneg.cpp) | N/A |
| `0x800D3F1C`<br>`0x800E09A8` | NATNEG Fixes / Telemetry | Send Connection Matrix to Host and Server | ✅ | [dwc_main.cpp](/payload/dwc/dwc_main.cpp)<br>[dwc_match.cpp](/payload/dwc/dwc_match.cpp)<br>[ConnectionMatrix.cpp](/payload/wiimmfi/ConnectionMatrix.cpp) | N/A |
| `0x800D8354` | NATNEG Fixes | Improved Next NATNEG Target Choosing Algorithm | ☑️<br>(Branch from `0x800D80D0` to `0x800D8360` and replaced instruction at `0x800D8360`) | [dwc_match.cpp](/payload/dwc/dwc_match.cpp)<br>[Natneg.cpp](/payload/wiimmfi/Natneg.cpp) | Removed various pointless checks and checks related to Auto Reconnect |
| `0x800D94F0`<br>`0x800E5980`<br>`0x800E5B14` | NATNEG Fixes | Parse Custom Match Commands | ✅ | [dwc_match.cpp](/payload/dwc/dwc_match.cpp)<br>[Natneg.cpp](/payload/wiimmfi/Natneg.cpp) | <ul><li>Storing RESV command data is not implemented due to the data being unused</li><li>Support for CTGP's custom commands will not be implemented</li></ul> |
| `0x800D9754` | NATNEG Fixes | Parse SYN Packets in Additional States | ✅ | [dwc_match.cpp](/payload/dwc/dwc_match.cpp) | N/A |
| `0x800DA7D0`<br>`0x800DA7D4`<br>`0x800DA7D8` | NATNEG Fixes | Send Failed Connection Matrix to Host | ✅ | [dwc_match.cpp](/payload/dwc/dwc_match.cpp)<br>[MatchCommand.cpp](/payload/wiimmfi/MatchCommand.cpp) | N/A |
| `0x800DBE30` | Auto Reconnect | Handle P2P Status Messages While Offline | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800DC21C` | Telemetry | Report Host Disconnections | ☑️<br>(Changed to three hooks at `0x800DDF40`, `0x800DE1E4` and `0x800E6A14`) | [dwc_match.cpp](/payload/dwc/dwc_match.cpp)<br>[Reporting.cpp](/payload/wiimmfi/Reporting.cpp) | N/A |
| `0x800DC49C` | Auto Reconnect | Stop People From Joining During Reconnect | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800DCA18` | NATNEG Fixes | Store Reservations in Queue | ⏭ | N/A | Patch not applied by the payload |
| `0x800DCEC8`<br>`0x800DCF98`<br>`0x800E57FC` | NATNEG Fixes | Send Failed Connection Matrix to Host | ⏭ | N/A | Patch not applied by the payload |
| `0x800E1A58` | NATNEG Fixes | Reduce SYN-ACK Timeout Time | ✅ | [dwc_match.cpp](/payload/dwc/dwc_match.cpp) | N/A |
| `0x800E1CA8` | NATNEG Fixes | Send Extra Packets on SYN-ACK Timeout | ✅ | [dwc_match.cpp](/payload/dwc/dwc_match.cpp)<br>[Natneg.cpp](/payload/wiimmfi/Natneg.cpp) | N/A |
| `0x800E58B8`<br>`0x800E58BC`<br> `0x800E58C8`<br>`0x800E58CC`<br>`0x800E58D0`<br>`0x800E58D8`<br>`0x800E58EC` | Security Fixes | Match Command Buffer Overflow Fix (GT2) | ☑️<br>(Merged into one call at `0x800E5924`) | [dwc_match.cpp](/payload/dwc/dwc_match.cpp) | Ported from WiiLink24's WFC Patcher and condensed |
| `0x800E5A2C`<br>`0x800E5A3C`<br> `0x800E5A40`<br>`0x800E5A50`<br>`0x800E5A54`<br>`0x800E5A64`<br>`0x800E5A74`<br>`0x800E5A80` | Security Fixes | Match Command Buffer Overflow Fix (QR2) | ☑️<br>(Merged into one call at `0x800E5AAC`) | [dwc_match.cpp](/payload/dwc/dwc_match.cpp) | Ported from WiiLink24's WFC Patcher and condensed |
| `0x800E6778` | NATNEG Fixes | Prevent Host Disconnection From Repeated NATNEG Failures | ✅ | [dwc_match.cpp](/payload/dwc/dwc_match.cpp)<br>[Natneg.cpp](/payload/wiimmfi/Natneg.cpp) | N/A |
| `0x800E7800` | NATNEG Fixes | Suspend Bug Fix | ☑️<br>(Moved to `0x800E77F4`) | [dwc_match.cpp](/payload/dwc/dwc_match.cpp) | Ported from WiiLink24's WFC Patcher |
| `0x800ED4A0`<br>`0x800ED558` | Auto Reconnect | Stub Some Errors | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x800ED784`<br>`0x800ED78C` | Payload Download | Payload Download Request | ⏭ | N/A | Porting unnecessary since the payload is not downloaded |
| `0x800EDEE8` | Authentication | Main Authentication Function | ⚠️ | [dwc_auth_interface.cpp](/payload/dwc/dwc_auth_interface.cpp)<br>[Auth.cpp](/payload/wiimmfi/Auth.cpp) | Accurate Data Sent:<ul><li>Console Certificate</li><li>Patcher Type</li><li>Console Type</li><li>Game Region</li><li>Device ID</li><li>Dolphin Version (if applicable)</li><li>Requested UPNP Port (if set)</li></ul>Faked Data Sent:<ul><li>Payload Version (Wiimmfi will otherwise reject access)</li></ul>Data Not Sent:<ul><li>Game IOS (Leseratte said it's not read by the server)</li><li>UPNP Settings (cannot be set without dedicated patchers)</li><li>Disc Version (unused)</li><li>Patcher Version (WSZST only)</li><li>Reconnect Data (Auto Reconnect not implemented)</li></ul> |
| `0x800EE098` | Authentication | Report Product Code on Dolphin | ✅ | [dwc_auth_interface.cpp](/payload/dwc/dwc_auth_interface.cpp)<br>[Auth.cpp](/payload/wiimmfi/Auth.cpp) | N/A |
| `0x800EE364`<br>`0x800EE36C` | Custom Error Messages | Store Custom Error Message | ⏭ | N/A | Replaced with offline error messages |
| `0x800EE74C` | Challenge Checking | Save Received Challenge | ✅ | [dwc_auth_interface.cpp](/payload/dwc/dwc_auth_interface.cpp)<br>[Challenge.cpp](/payload/wiimmfi/Challenge.cpp) | N/A |
| `0x800EE9F8` | Authentication | Parse Custom Response | ☑️<br>(Moved to `0x800EEA08`) | [dwc_auth_interface.cpp](/payload/dwc/dwc_auth_interface.cpp)<br>[Auth.cpp](/payload/wiimmfi/Auth.cpp) | <ul><li>Discard oversized messages and properly NULL-terminate them after decoding</li><li>Replace disgusting runtime hook replacements with fixed hooks</li></ul> |
| `0x800FCEDC` | Player Kicking | Parse Kick Requests | ⚠️<br>(Moved to `0x800FCEE8` and replaced instruction at `0x800FCEC8`) | [gpi.cpp](/payload/gs/gp/gpi.cpp)<br>[Kick.cpp](/payload/wiimmfi/Kick.cpp) | <ul><li>Kicking other players has been restricted to hosts to prevent the Phantom Racer Glitch</li><li>Custom kick message support not implemented yet</li></ul> |
| `0x801007D8` | Authentication | Report Certificate and Signed Token | ✅ | [gpiConnect.cpp](/payload/gs/gp/gpiConnect.cpp)<br>[Auth.cpp](/payload/wiimmfi/Auth.cpp) | N/A |
| `0x8010E094` | Port Binding | Retry on Different Port on Binding Failure | ✅ | [gt2Socket.cpp](/payload/gs/gt2/gt2Socket.cpp) | Avoid pointless use of static variables |
| `0x80111534` | Challenge Checking | Send Saved Challenge | ✅ | [qr2.cpp](/payload/gs/qr2/qr2.cpp)<br>[Challenge.cpp](/payload/wiimmfi/Challenge.cpp) | Hook rewritten to avoid overwriting existing parameters or overflowing the buffer |
| `0x8011AB28`<br>`0x8011AB30` | NATify Fixes | Send NATify Result | ☑️<br>(Added extra write to `0x8011AB2C`) | [natneg.cpp](/payload/gs/natneg/natneg.cpp)<br>[Natify.cpp](/payload/wiimmfi/Natify.cpp) | Replaced unsafe store |
| `0x8011B478` | NATNEG Fixes | Reduce CONNECT_PING Retry Time | ✅ | [natneg.cpp](/payload/gs/natneg/natneg.cpp) | N/A |
| `0x8011B4B0` | NATNEG Fixes | Ignore Retry Time on NATNEG Success | ✅ | [natneg.cpp](/payload/gs/natneg/natneg.cpp) | N/A |
| `0x801937E0`<br>`0x801938F8` | "Security" Fixes | IOS Operation "Protection" | ⏭ | N/A | Porting skipped for the aforementioned reasons |
| `0x801D4F10`<br>`0x801D4F2C` | Payload Download | Payload Download CA Replacement | ⏭ | N/A | Porting unnecessary since the payload is not downloaded |
| `0x8023B0E0` | Player Kicking | Reset Kick Flag | ☑️<br>(Moved to `0x80554728`) | N/A | N/A |
| `0x80279D58`<br>`0x80279DA4`<br>`0x80279DE4`<br>`0x8027A428`<br>`0x8027A4A8`<br>`0x8027AD68`<br>`0x8027B4D8`<br>`0x8027BEF0`<br>`0x8027D091`<br>`0x8027DCAB`<br>`0x8027DCC7`<br>`0x8027DCE3`<br>`0x8027DE33`<br>`0x8027DEB7`<br>`0x8027E0A0`<br>`0x8089A6B8`<br>`0x8089ABD0`<br>`0x8089AC25`<br>`0x8089AC85`<br>`0x8089AD12` | Domain Replacements | N/A | ✅ | [Domains.cpp](/payload/wiimmfi/Domains.cpp) | N/A |
| `0x8027A688` | Auto Reconnect | Handle Login | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x80514D58`<br>`0x80514D7C` | Bug Fixes | Invalid Item Point Antifreeze | ☑️<br>(Overrides function at `0x80514D3C`) | [CourseMap.cpp](/payload/game/system/CourseMap.cpp) | Entire function reimplemented to provide extra flexibility |
| `0x80518AFC`<br>`0x80518B20` | Bug Fixes | Invalid Cannon Point Antifreeze | ☑️<br>(Overrides function at `0x80518AE0`) | [CourseMap.cpp](/payload/game/system/CourseMap.cpp) | Entire function reimplemented to provide extra flexibility |
| `0x80519560` | Telemetry | Report Track SHA1 Hash | ☑️<br>(Overrides function at `0x80519508`) | [DvdArchive.cpp](/payload/game/system/DvdArchive.cpp)<br>[Reporting.cpp](/payload/wiimmfi/Reporting.cpp) | <ul><li>The track hash will not be calculated if the game is in offline mode</li><li>Replaced various ugly checks to detect a track file with a simple path string check</li><li>Hint: mods can cache and reuse the calculated hashes for other purposes or simply to reduce loading times</li></ul> |
| `0x8051B69C` | Frameskip | N/A | ⏭ | N/A | Frameskip will not be reimplemented |
| `0x80533660` | Telemetry | Report Race Finish and Battle Results | ☑️<br>(Moved to `0x8053369C`) | [RaceManager.cpp](/payload/game/system/RaceManager.cpp)<br>[Reporting.cpp](/payload/wiimmfi/Reporting.cpp) |<ul><li>The race finish will not be reported if the race is offline</li><li>The battle results are not reported because the payload fails to copy them over before sending the report</li></ul> |
| `0x805348CC` | Telemetry | Report Race Finish Time | ☑️<br>(Moved to `0x8053490C`) | [RaceManager.cpp](/payload/game/system/RaceManager.cpp)<br>[Reporting.cpp](/payload/wiimmfi/Reporting.cpp) | The finish time will not be reported if the race is offline or the player is not local |
| `0x8053511c` | Bug Fixes | Ultra Shortcut Fix | ☑️<br>(Moved to `0x805350DC`) | [RaceManager.cpp](/payload/game/system/RaceManager.cpp) | Rewritten in C++ to allow mods more control over the fix's application |
| `0x80535C78` | Accurate Timing | Update Race Frame Counter | ☑️<br>(Added a extra hook at `0x80535C7C`) | [TimerManager.cpp](/payload/game/system/TimerManager.cpp)<br>[Delay.cpp](/payload/wiimmfi/Delay.cpp) | N/A |
| `0x8053F3F4` | Player Kicking | Cancel Race Support | ☑️<br>(Branch from `0x8053F39C` to `0x8053F444`) | [RaceModeOnlineVs.cpp](/payload/game/system/RaceModeOnlineVs.cpp) | Rewritten in C++ to allow mods to easily end the race on command |
| `0x8054DF88` | Frameskip | Disable Model Drawing while Lagging | ⏭ | N/A | Pointless patch as the hooked function is never called by the game |
| `0x805543A4` | Telemetry | Report Course Subfile SHA1 Hashes | ✅ | [RaceScene.cpp](/payload/game/scene/RaceScene.cpp)<br>[Reporting.cpp](/payload/wiimmfi/Reporting.cpp) | The hashes are not computed if the race is offline |
| `0x80562AD0` | Frameskip | Disable Model Drawing while Lagging | ⏭ | N/A | Frameskip ill not be implemented |
| `0x805845D8` | Bug Fixes | Invalid Item Point Antifreeze | ⏭ | N/A | Pointless hook that replaces a null pointer check |
| `0x80589ACC` | Bug Fixes | Halfpipe Fix | ✅ | [KartNetReceiver.cpp](/payload/game/kart/KartNetReceiver.cpp) | <ul><li>Removed pointless null pointer check</li><li>Used a couple padding bytes in the KartNetReceiver class instead of a static array</li></ul> |
| `0x80591B70` | Telemetry and "Anticheat" | Report Common.szs Subfile SHA1 Hashes and "Detect" Gecko Codes | ✅ | [KartParam.cpp](/payload/game/kart/KartParam.cpp)<br>[Reporting.cpp](/payload/wiimmfi/Reporting.cpp) | <ul><li>The hashes will not be calculated if the game is offline</li><li>The Gecko code checks are not ported due to ease of bypass, potential false reports caused by mods and lack of use for bans</li></ul> |
| `0x805CDDC8` | Custom Messages | Apply Message Replacements | ⏭ | N/A | Features implemented separately due to high chances of clashing with existing patches:<ul><li>Custom Error Messages: replaced with offline error messages</li><li>Custom Kick Messages: not yet ported since it is currently unused, but it will be implemented separately</li><li>Console Assignment Message: logic moved to `0x808BFF8C`</li> |
| `0x805CE55C` | Frameskip | Mess with Text Rendering Code | ⏭ | N/A | Frameskip should not mess with BMG escape sequences |
| `0x805D2EF8`<br>`0x805D2F00` | Bug Fixes | Invalid Friend Code Antifreeze | ✅ | [FriendList.cpp](/payload/game/system/FriendList.cpp) | N/A |
| `0x805D8CF4`<br>`0x805D9044`<br>`0x806437CC`<br>`0x80643CB8`<br>`0x80643CCC`<br>`0x80644404`<br>`0x8064AAAC` | Auto Reconnect | Voting Screen Text Update | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x805DCE34` | Telemetry | Report Room Start | ✅ | [FriendRoomMessageSelectPage.cpp](/payload/game/ui/page/FriendRoomMessageSelectPage.cpp)<br>[Reporting.cpp](/payload/wiimmfi/Reporting.cpp) | Removed pointless `snprintf` call |
| `0x80600D10` | Data Sharing Consent | Revoke Custom Data Sharing Consent Flag | ✅ | [OptionMessagePage.cpp](/payload/game/ui/page/OptionMessagePage.cpp) | N/A |
| `0x8064ECB4`<br>`0x8064F074`<br>`0x8064F60C`<br>`0x8064F610`<br>`0x8064F618`<br>`0x8064F61C`<br>`0x8064F620`<br>`0x8064F644` | Auto Reconnect | Handle Exiting Race while Offline | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x80654400` | Bug Fixes | Ignore Reported Lag Frames | ✅ | [RKNetPacketCreator.cpp](/payload/game/net/RKNetPacketCreator.cpp) | N/A |
| `0x806579B0` | Various | Main Wiimmfi Network Loop | ✅ | N/A | Implemented:<ul><li>Report match state changes to the server</li><li>Report suspend changes to the server</li><li>Execute scheduled kicks</li><li>Report AID/PID matrix to the server</li><li>Report host AID to the server</li><li>Calculate frame lag</li><li>Report frame count to the server</li><li>Stop NATNEG after 11 seconds have passed since the last match state change (unsure)</li><li>Report VS and BT region to the server</li><li>Report SELECT packet information to the server</li><li>Report first four PIDs to the server (???)</li></ul>Will not be implemented:<ul><li>Auto Reconnect update (feature won't be implemented)</li><li>Item cheat self-reporting (pointless measure)</li><li>Countdown item usage self-reporting (pointless measure)</li></ul> |
| `0x80657A6C` | Auto Reconnect | Fix Main Thread | ⏭ | N/A | Auto Reconnect will not be implemented |
| `0x80658610` | Security Fixes | RCE Fix | ⚠️ | [RKNetController.cpp](/payload/game/net/RKNetController.cpp)<br>[Security.cpp](/payload/wiimmfi/Security.cpp) | Ported from WiiLink24, providing the following enhancements:<ul><li>Full support for custom packet sizes</li><li>Packet data is also validated and not just the size (not yet implemented)</li><li>Only the host is able to disconnect the offending player to avoid the Phantom Racer Glitch</li></ul> |
| `0x806591F4`<br>`0x80659248` | Telemetry | Obtain VS/BT Regions | ⏭ | N/A | Removed disgusting runtime hooks and replaced them with a sane solution |
| `0x8065DF44` | Security Fixes | ITEM Packet Data Validation | ⚠️ | N/A | Integrated into RCE Fix (not implemented yet) |
| `0x8065FF5C` | Bug Fixes | Reset Room Stall Timer | ✅ | [RKNetSelectHandler.cpp](/payload/game/net/RKNetSelectHandler.cpp)<br>[RoomStall.cpp](/payload/wiimmfi/RoomStall.cpp) | N/A |
| `0x80660330` | Bug Fixes | Room Stall Prevention | ✅ | [RKNetSelectHandler.cpp](/payload/game/net/RKNetSelectHandler.cpp)<br>[RoomStall.cpp](/payload/wiimmfi/RoomStall.cpp) | <ul><li>The timeout timer will not be reset between SELECT phases and instead acts as a global timer</li><li>Additional fields are checked when determining who to kick</li><li>The timeout timer has been increased to 90 seconds</li></ul> |
| `0x80760A88` | Bug Fixes | Thwomp Antifreeze | ✅ | [ObjDossun.cpp](/payload/game/obj/ObjDossun.cpp) | N/A |
| `0x8079BF88` | Security Fixes | EVENT Packet Data Validation | ⚠️ | N/A | Integrated into RCE Fix (not implemented yet) |
| `0x807A1914` | Bug Fixes | Stationary Item Collision Momentum Fix | ✅ | [ItemObj.cpp](/payload/game/item/ItemObj.cpp) | N/A |
| `0x807BC940` | "Anticheat" | Store Item for Cheat Detection | ⏭ | N/A | Not ported due to the measure basically amounting to self-reporting, which is too fragile and easily bypassed |
| `0x808BFF8C` | Authentication | Display Console Assignment Message | ✅ | [WifiMenuPage.cpp](/payload/game/ui/page/WifiMenuPage.cpp) | Replaced disgusting runtime hook with fixed hook |
| `0x808D4100` | Frameskip | Display Debug Data | ⏭ | N/A | This should not be in the regular payload |
| `0x808D410C` | Frameskip | N/A | ⏭ | N/A | Hook does literally nothing |

### New Hooks
The table below lists all the new hooks introduced by OpenPayload and their purpose:

| **Hook Address(es)** | **Category** | **Purpose** | **Code** | **Notes/Changes** |
|----------------------|--------------|-------------|:--------:|-------------------|
| `0x8011BC38` | NATNEG Fixes | Skip Unnecessary Delay | [natneg.cpp](/payload/gs/natneg/natneg.cpp) | Ported from WiiLink24 WFC |
| `0x80554728` | Various | Reset Values Before Race Start | N/A | N/A
| `0x80657A6C` | Authentication | Delete Expired Token | [RKNetController.cpp](/payload/game/net/RKNetController.cpp) | N/A |
| `0x808BFB74` | Custom Error Messages | Display Custom Error Message | [WifiDisconnectPage.cpp](/payload/game/ui/page/WifiDisconnectPage.cpp) | Virtual function override |
