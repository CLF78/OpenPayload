#include <common/Common.h>
#include <revolution/dvd/dvd.h>
#include <revolution/os/OSExec.h>
#include <revolution/os/OSModule.h>
#include <revolution/os/OSThread.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DVDDiskID diskInfo;
    u32 standardBootCode;
    u32 diskVersion;
    u32 memorySize;
    u32 consoleType;
    u32 arenaLo;
    u32 arenaHi;
    u32 fstStart;
    u32 fstMaxLength;
} OSBootInfo;

typedef struct {
    u32 debuggerPresent;
    u32 exceptionMask;
    void* exceptionDestination;
    void* exceptionReturn;
} DBInterface;

typedef struct {
    u32 debugMonitorSize;
    u32 simulatedMem1Size;
    u32 argOffset;
    u32 debugFlag;
    u32 TRKLocation;
    u32 TRKSize;
    u32 countryCode;
    u32 numDisks;
    u32 longFilenameFlag;
    u32 padSpec;
    u32 dolSizeLimit;
    u32 simulatedMem2Size;
    u32 deviceCheckCode;
} OSDiskHeaderInfo;

typedef struct {
    u32 MEM1Size;
    u32 MEM1SimSize;
    u32 MEM1SecureBoundary;
    void* MEM1ArenaLo;
    void* MEM1ArenaHi;
    u32 reserved;
    u32 MEM2Size;
    u32 MEM2SimSize;
    u32 MEM2SecureBoundary;
    void* MEM2ArenaLo;
    void* MEM2ArenaHi;
    u32 reserved2;
    void* IPCArenaLo;
    void* IPCArenaHi;
    u32 hollywoodRev;
    u32 productVersion;
    u32 iosVersion;
    u32 iosBuild;
    void* diBufferLo;
    void* diBufferHi;
    void* scBufferLo;
    void* scBufferHi;
    u32 ddrVendorId;
    u32 bootromTarget;
    u32 apploaderTarget;
    u16 bootProgramVersion;
    u32 syncAHBPI;
    u32 shutdown;
} OSLoMem;

// 0x80000000 MEM1 start
volatile OSBootInfo __OSBootInfo AT_ADDR(0x80000000);
volatile DBInterface __DBInterface AT_ADDR(0x80000040);

// 0x80000050 - 0x8000005F reserved
vu32 __DBIntegrator[9] AT_ADDR(0x80000060);

// 0x80000084 - 0x800000BF reserved
vu32 __OSCurrContextPhysical AT_ADDR(0x800000C0);
vu32 __OSInterruptMask AT_ADDR(0x800000C4);
vu32 __OSUserInterruptMask AT_ADDR(0x800000C8);
vu32 __OSTVMode AT_ADDR(0x800000CC);
vu32 __OSARAMSize AT_ADDR(0x800000D0);
volatile OSContext* __OSCurrentContext AT_ADDR(0x800000D4);
volatile OSContext* __OSFPUContext AT_ADDR(0x800000D8);
volatile OSThreadQueue __OSActiveThreadQueue AT_ADDR(0x800000DC);
volatile OSThread* __OSCurrentThread AT_ADDR(0x800000E4);
vu32 __OSDebugMonSize AT_ADDR(0x800000E8);
vu32 __OSDebugMonLocation AT_ADDR(0x800000EC);
vu32 __OSSimSize AT_ADDR(0x800000F0);
volatile OSDiskHeaderInfo* __OSDiskHeaderInfo AT_ADDR(0x800000F4);
vu32 __OSBusClockSpeed AT_ADDR(0x800000F8);
vu32 __OSCoreClockSpeed AT_ADDR(0x800000FC);

// 0x80000100 - 0x800017FF exception vector area
// 0x80001800 - 0x80002FFF return to loader code
vu32 __CodeHandlerStart AT_ADDR(0x800018A8);
volatile void* __OSExceptionTable[16] AT_ADDR(0x80003000);
volatile void* __OSInterruptTable[32] AT_ADDR(0x80003040);
vu32 __EXIProbeStartTime[2] AT_ADDR(0x800030C0);
volatile OSModuleQueue __OSModuleList AT_ADDR(0x800030C8);
volatile void* __OSModuleStringTable AT_ADDR(0x800030D0);
vu32 __OSBootTotalBytes AT_ADDR(0x800030D4);
vs64 __OSSystemTime AT_ADDR(0x800030D8);
vu16 __OSWPADFixMode AT_ADDR(0x800030E0);
vu8 __OSIsRebooted AT_ADDR(0x800030E2);
vu8 __OSGameChoice AT_ADDR(0x800030E3);
vu16 __OSPadButton AT_ADDR(0x800030E4);
vu16 __DVDDeviceCode AT_ADDR(0x800030E6);
vu8 __OSDebugFlag AT_ADDR(0x800030E8);
vu8 __OSPadSpec AT_ADDR(0x800030E9);
vu16 __OSGameChoice2 AT_ADDR(0x800030EA);
vu32 __OSDOLOffsetToBoot AT_ADDR(0x800030EC);
volatile OSExecParams* __OSExecParams AT_ADDR(0x800030F0);
vs32 __OSCurrentTGCOffset AT_ADDR(0x800030F4);

// 0x800030F8 - 0x800030FF reserved
volatile OSLoMem __OSBootInfo2 AT_ADDR(0x80003100);
volatile OSModuleQueue __OSRSOModuleList AT_ADDR(0x80003168);
vu32 __NANDSysBlockUsage AT_ADDR(0x80003170);
vu32 __NANDSysInodeUsage AT_ADDR(0x80003174);
vu32 __NANDUserBlockUsage AT_ADDR(0x80003178);
vu32 __NANDUserInodeUsage AT_ADDR(0x8000317C);
volatile char __OSAppGamename[4] AT_ADDR(0x80003180);
vu8 __OSAppType AT_ADDR(0x80003184);
vu8 __OSDriveSavingMode AT_ADDR(0x80003185);
vu8 __OSNandbootInfoFlag AT_ADDR(0x80003186);
vu8 __OSLockedFlag AT_ADDR(0x80003187);
vu32 __OSMinimumIOSVersion AT_ADDR(0x80003188);
vu32 __OSLaunchCode AT_ADDR(0x8000318C);
vu32 __OSReturnCode AT_ADDR(0x80003190);
vu32 __OSPartitionType AT_ADDR(0x80003194);
vu32 __OSDataPartitionOffset AT_ADDR(0x80003198);
vu8 __OSDeviceCheckCode AT_ADDR(0x8000319C);

// 0x8000319D - 0x800031A1 reserved
vu8 __OSWlanChan AT_ADDR(0x800031A2);

// 0x800031A3 - 0x800031BF reserved
vu32 __NWC24Data[2] AT_ADDR(0x800031C0);

// 0x800031C8 - 0x800031FF reserved
vu64 __OSLastTitleID AT_ADDR(0x80003200);

// 0x80003208 - 0x800033FE free area
volatile void* __PayloadStart AT_ADDR(0x80003208);
volatile void* __PayloadEnd AT_ADDR(0x8000320C);

// 0x800033FF reserved
vu8 __OSBootstrapCode[0x400] AT_ADDR(0x80003400);
vu8 __OSProductInfo[0x100] AT_ADDR(0x80003800);

// 0x80003900 - 0x80003EFF free area
// 0x80003F00 start of working area

#ifdef __cplusplus
}
#endif
