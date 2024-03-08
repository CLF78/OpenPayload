#include <common/Common.hpp>
#include <revolution/ios.h>

namespace DolphinDevice {

enum Ioctlv {

    // 5.0-11186 and onwards
    GET_ELAPSED_TIME = 1, // In = None, Out = u32
    GET_VERSION = 2,     // In = None, Out = char[]
    GET_SPEED_LIMIT = 3,  // In = None, Out = u32
    SET_SPEED_LIMIT = 4,  // In = u32, Out = None
    GET_CPU_SPEED = 5,    // In = None, Out = u32

    // 5.0-12058 and onwards
    GET_REAL_PRODUCT_CODE = 6, // In = None, Out = char[]

    // 5.0-17155 and onwards
    DISCORD_SET_CLIENT = 7,   // In = char[], Out = None
    DISCORD_SET_PRESENCE = 8, // In = (char[], char[], char[], char[], char[], s64, s64, u32, u32), Out = None
    DISCORD_RESET = 9, // In = None, Out = None

    // 5.0-17856 and onwards
    GET_SYSTEM_TIME = 10, // In = None, Out = u64
};

bool Open();
u32 GetElapsedTime();
const char* GetVersion();
const char* GetRealProductCode();

} // namespace DolphinDevice
