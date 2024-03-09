#include <common/Common.h>
#include <revolution/base/PPCWGPipe.h>

#ifdef __cplusplus
extern "C" {
#endif

vu16 __CPRegs[0x33] AT_ADDR(0xCC000000);
vu16 __PERegs[0x100] AT_ADDR(0xCC001000);
vu16 __VIRegs[0x3A] AT_ADDR(0xCC002000);
vu32 __PIRegs[0xD] AT_ADDR(0xCC003000);
vu16 __MEMRegs[0x40] AT_ADDR(0xCC004000);
vu16 __DSPRegs[0x20] AT_ADDR(0xCC005000);
vu32 __DIRegs[0x10] AT_ADDR(0xCC006000);
vu32 __SIRegs[0x40] AT_ADDR(0xCC006400);
vu32 __EXIRegs[0x10] AT_ADDR(0xCC006800);
vu32 __AIRegs[0x8] AT_ADDR(0xCC006C00);
vu32 __ACRRegs[0x89] AT_ADDR(0xCD000000);
volatile PPCWGPipe __GXFIFO AT_ADDR(0xCC008000);
vu16 __LT_CHIPREVID AT_ADDR(0xCD8005A0);

#ifdef __cplusplus
}
#endif
