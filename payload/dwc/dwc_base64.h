#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

int DWC_Base64Encode(const char* src, const ulong srclen, char* dst, const ulong dstlen);
int DWC_Base64Decode(const char* src, const ulong srclen, char* dst, const ulong dstlen);

#define DWC_Base64GetEncodedSize(x) (((x) / 3 + ((x) % 3 != 0)) * 4)

#ifdef __cplusplus
}
#endif
