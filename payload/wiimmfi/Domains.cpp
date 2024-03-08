#include <common/Common.hpp>

// NOTE: regular Kamek does not support kmWriteArea, up to you to deal with this

// Authentication server
kmWriteArea(0x8027A428, "http://naswii.wiimmfi.de/ac");

// Profanity check server (i think)
kmWriteArea(0x8027A4A8, "http://naswii.wiimmfi.de/pr");

// Various domain replacements
kmWriteArea(0x8027AD68, "wiimmfi.de"); // AVAILABLE
kmWriteArea(0x8027B4D8, "wiimmfi.de"); // GPCM
kmWriteArea(0x8027BEF0, "wiimmfi.de"); // GPSP
kmWriteArea(0x8027D091, "wiimmfi.de"); // MASTER
kmWriteArea(0x8027DCAB, "wiimmfi.de"); // NATNEG1
kmWriteArea(0x8027DCC7, "wiimmfi.de"); // NATNEG2
kmWriteArea(0x8027DCE3, "wiimmfi.de"); // NATNEG3
kmWriteArea(0x8027DE33, "wiimmfi.de"); // MS

// SAKE domains for completeness' sake (pun intended)
kmWriteArea(0x80279D58, "http://%s.sake.gs.wiimmfi.de/SakeStorageServer/StorageServer.asmx");
kmWriteArea(0x80279DA4, "http://%s.sake.gs.wiimmfi.de/SakeFileServer/upload.asmx");
kmWriteArea(0x80279DE4, "http://%s.sake.gs.wiimmfi.de/SakeFileServer/download.asmx");
kmWriteArea(0x8027DEB7, "wiimmfi.de");
kmWriteArea(0x8027E0A0, "http://%s.sake.gs.wiimmfi.de/SakeStorageServer/StorageServer.asmx");
kmWriteArea(0x8089A6B8, "http://mariokartwii.sake.gs.wiimmfi.de/SakeFileServer/ghostdownload.aspx?gameid=1687&region=0");
kmWriteArea(0x8089ABD0, "http://mariokartwii.race.gs.wiimmfi.de/RaceService/NintendoRacingService.asmx");
kmWriteArea(0x8089AC25, "http://mariokartwii.race.gs.wiimmfi.de/RaceService/NintendoRacingService.asmx");
kmWriteArea(0x8089AC85, "%s://mariokartwii.sake.gs.wiimmfi.de/SakeFileServer/ghostupload.aspx?gameid=%d&regionid=%d&courseid=%d&score=%d&pid=%d&playerinfo=%s%s");
kmWrite8(0x8089AD16, '\0');
