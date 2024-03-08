#include <common/Common.hpp>
#include <dwc/dwc_match.h>
#include <gs/common/gsAvailable.h>
#include <gs/common/gsPlatformUtil.h>
#include <gs/common/gsSocketRevolution.h>
#include <gs/natneg/natify.h>
#include <gs/natneg/natneg.h>
#include <platform/string.h>
#include <wiimmfi/Natify.hpp>

namespace Wiimmfi {
namespace Natify {

bool sDoingNatify;
NatifyData sNatifyData;

void Callback(BOOL success, NAT* theNat) {

    // If NATify was successful, copy the data over
    sDoingNatify = false;
    if (success) {

        DEBUG_REPORT("[NATIFY] NATify done for PID %d\n", stpMatchCnt->profileId)
        sNatifyData.profileId = stpMatchCnt->profileId;
        sNatifyData.portRestricted = nat.portRestricted;
        sNatifyData.ipRestricted = nat.ipRestricted;
        sNatifyData.natPromiscuity = nat.promiscuity;
        sNatifyData.natType = nat.type;
        sNatifyData.natMappingScheme = nat.mappingScheme;
        sNatifyData.qr2Compatible = nat.qr2Compatible;
    }
}

int CopyData(u8* buffer) {
    memcpy(buffer, &sNatifyData, sizeof(sNatifyData));
    return sizeof(sNatifyData) + 1;
}

void Start() {
    DEBUG_REPORT("[NATIFY] Started NATify procedure\n")
    sDoingNatify = true;
    NNStartNatDetection(Callback);
}

void Update() {
    if (sDoingNatify)
        NegotiateThink(nullptr);
}

} // namespace Natify
} // namespace Wiimmfi
