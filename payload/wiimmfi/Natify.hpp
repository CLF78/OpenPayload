#include <common/Common.hpp>
#pragma pack(push, 1)

namespace Wiimmfi {
namespace Natify {

////////////////
// Structures //
////////////////

    // The data saved on NATify success
    struct NatifyData {
        u32 profileId;
        bool portRestricted;
        bool ipRestricted;
        u8 natPromiscuity;
        u8 natType;
        u8 natMappingScheme;
        bool qr2Compatible;
    };

    ///////////////
    // Functions //
    ///////////////

    // Copies the NATify result data into the given buffer
    // Returns the size of the copied data
    int CopyData(u8* buffer);

    // Start NATify procedure
    void Start();

    // Update NATify procedure until it succeeds
    void Update();

} // namespace Natify
} // namespace Wiimmfi

#pragma pack(pop)
