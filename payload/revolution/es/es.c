#include <common/Common.h>
#include <revolution/es/es.h>
#include <revolution/ios.h>

s32 ES_GetDeviceCert(u8* outBuf) {
	if (__esFd < 0)
        return ES_ERR_INVALID;

	if (!outBuf)
        return ES_ERR_INVALID;

	if ((u32)outBuf & 0x1F)
        return ES_ERR_INVALID;

    ALIGN(32) IOSIoVector vec = {outBuf, IOSECCCertSize};
    IOS_Ioctlv(__esFd, ES_CMD_GET_DEVICE_CERT, 0, 1, &vec);
    return ES_ERR_OK;
}

s32 ES_Sign(u8* source, u32 size, u8* sig, u8* cert) {
	if (__esFd < 0)
        return ES_ERR_INVALID;

 	if (!source || !size || !sig || !cert)
        return ES_ERR_INVALID;

 	if ((u32)source & 0x1F || (u32)sig & 0x1F || (u32)cert & 0x1F)
        return ES_ERR_INVALID;

    ALIGN(32) IOSIoVector vec[3] = {
        {source, size}, {sig, IOSECCSigSize}, {cert, IOSECCCertSize}
    };

 	IOS_Ioctlv(__esFd, ES_CMD_SIGN, 1, 2, vec);
    return ES_ERR_OK;
}
