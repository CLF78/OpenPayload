#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

inline u16 NETReadSwappedBytes16(const u16* src) {
    return (u16)__lhbrx(src, 0);
}

inline u32 NETReadSwappedBytes32(const u32* src) {
    return (u32)__lwbrx(src, 0);
}

inline void NETWriteSwappedBytes16(u16* dst, u16 val) {
    __sthbrx(val, dst, 0);
}

inline void NETWriteSwappedBytes32(u32* dst, u32 val) {
    __stwbrx(val, dst, 0);
}

u32 NETCalcCRC32(const void* data, u32 dataSize);

typedef struct {
    u32 h[5]; // H0, H1, H2, H3, H4
    u8 block[64]; // current message block
    u32 pool; // current message length
    u32 blocks_low; // total blocks in bytes
    u32 blocks_high;
} NETSHA1Context;

void NETSHA1Init(NETSHA1Context* context);
void NETSHA1Update(NETSHA1Context* context, const void* input, u32 length);
void NETSHA1Fill(NETSHA1Context* context, u8 input, u32 length);
void NETSHA1GetDigest(NETSHA1Context* context, void* digest);

inline void NETCalcSHA1(void* digest, const void* input, u32 length) {
    NETSHA1Context context;

    NETSHA1Init(&context);
    NETSHA1Update(&context, input, length);
    NETSHA1GetDigest(&context, digest);
}

#ifdef __cplusplus
}
#endif
