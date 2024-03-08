#include <common/Common.hpp>

struct WifiDisconnectInfo {

    enum ErrorCategory {
        ERROR_NONE,
        ERROR_WITH_CODE,
        ERROR_OFFENSIVE_MII,
        ERROR_FRIEND_JOIN,
        ERROR_GENERIC,
        ERROR_UNRECOVERABLE,
    };

    void reset();

    s32 errorCategory;
    s32 errorCode;
};
