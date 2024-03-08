#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

///////////////
// Registers //
///////////////
#define ECID_U 924
#define ECID_M 925
#define ECID_L 926

//////////
// ECID //
//////////
#define DEFAULT_ECID_U 0x0D96E200
#define DEFAULT_ECID_M 0x1840C00D
#define DEFAULT_ECID_L 0x82BB08E8

///////////
// FPSCR //
///////////
typedef enum {
    FPSCR_FX     = BIT_FLAG(31), // Exception summary
    FPSCR_FEX    = BIT_FLAG(30), // Enabled exception summary
    FPSCR_VX     = BIT_FLAG(29), // Invalid operation
    FPSCR_OX     = BIT_FLAG(28), // Overflow exception
    FPSCR_UX     = BIT_FLAG(27), // Underflow exception
    FPSCR_ZX     = BIT_FLAG(26), // Zero divide exception
    FPSCR_XX     = BIT_FLAG(25), // Inexact exception
    FPSCR_VXSNAN = BIT_FLAG(24), // SNaN
    FPSCR_VXISI  = BIT_FLAG(23), // Infinity - Infinity
    FPSCR_VXIDI  = BIT_FLAG(22), // Infinity / Infinity
    FPSCR_VXZDZ  = BIT_FLAG(21), // 0 / 0
    FPSCR_VXIMZ  = BIT_FLAG(20), // Infinity * 0
    FPSCR_VXVC   = BIT_FLAG(19), // Invalid compare
    FPSCR_FR     = BIT_FLAG(18), // Fraction rounded
    FPSCR_FI     = BIT_FLAG(17), // Fraction inexact
    FPSCR_VXSOFT = BIT_FLAG(10), // Software request
    FPSCR_VXSQRT = BIT_FLAG(9), // Invalid square root
    FPSCR_VXCVI  = BIT_FLAG(8), // Invalid integer convert
    FPSCR_VE     = BIT_FLAG(7), // Invalid operation exception enable
    FPSCR_OE     = BIT_FLAG(6), // Overflow exception enable
    FPSCR_UE     = BIT_FLAG(5), // Underflow exception enable
    FPSCR_ZE     = BIT_FLAG(4), // Zero divide exception enable
    FPSCR_XE     = BIT_FLAG(3), // Inexact exception enable
    FPSCR_NI     = BIT_FLAG(2), // Non-IEEE mode
} FPSCR;

///////////////
// Functions //
///////////////

inline u32 PPCGetECID_U() {
    register u32 val;
    __asm__ (mfspr val, ECID_U);
    return val;
}

inline u32 PPCGetECID_M() {
    register u32 val;
    __asm__ (mfspr val, ECID_M);
    return val;
}

inline u32 PPCGetECID_L()  {
    register u32 val;
    __asm__ (mfspr val, ECID_L);
    return val;
}

#ifdef __cplusplus
}
#endif
