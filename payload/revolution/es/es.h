#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ES_ERR_OK                          = 0,
    ES_ERR_INCORRECT_CERT_TYPE         = -1001,
    ES_ERR_GENKEY_FAILED               = -1002,
    ES_ERR_VERIFY_SIG_FAILED           = -1003,
    ES_ERR_CANNOT_OPEN_FILE            = -1004,
    ES_ERR_INCORRECT_PUBKEY_TYPE       = -1005,
    ES_ERR_CERT_ISSUER_MISMATCH        = -1006,
    ES_ERR_ENCRYPTION_FAILED           = -1007,
    ES_ERR_FILE_OPEN_FAILED            = -1008,
    ES_ERR_FILE_READ_FAILED            = -1009,
    ES_ERR_FILE_WRITE_FAILED           = -1010,
    ES_ERR_TMD_NUM_CONTENTS            = -1011,
    ES_ERR_INCORRECT_SIG_TYPE          = -1012,
    ES_ERR_INCORRECT_SIG_LENGTH        = -1013,
    ES_ERR_INCORRECT_CERT_LENGTH       = -1014,
    ES_ERR_DEV                         = -1015,
    ES_ERR_MAXFD                       = -1016,
    ES_ERR_INVALID                     = -1017,
    ES_ERR_FS_CONNECTION_FAILED        = -1018,
    ES_ERR_UNSUPPORTED_TRANSFER_SOURCE = -1019,
    ES_ERR_DEVICE_ID_MISMATCH          = -1020,
    ES_ERR_INCORRECT_CONTENT_SIZE      = -1021,
    ES_ERR_HASH_MISMATCH               = -1022,
    ES_ERR_INCORRECT_CONTENT_COUNT     = -1023,
    ES_ERR_OUT_OF_MEMORY               = -1024,
    ES_ERR_NO_TMD_FILE                 = -1025,
    ES_ERR_NO_RIGHT                    = -1026,
    ES_ERR_ISSUER_NOT_FOUND            = -1027,
    ES_ERR_NO_TICKET                   = -1028,
    ES_ERR_INCORRECT_TICKET            = -1029,
    ES_ERR_NOT_ENOUGH_SPACE            = -1030,
    ES_ERR_INCORRECT_BOOT_VERSION      = -1031,
    ES_ERR_UNKNOWN                     = -1032,
    ES_ERR_EXPIRED                     = -1033,
    ES_ERR_UNUSED                      = -1034,
    ES_ERR_INCORRECT_TITLE_VERSION     = -1035,
    ES_ERR_OS_TICKET_NOEXISTS          = -1036,
    ES_ERR_OS_CONTENT_NOEXISTS         = -1037,
    ES_ERR_NOT_EMPTY                   = -1038,
    ES_ERR_DISC_NAND_NO_TMD            = -1039,
    ES_ERR_NOEXISTS                    = -106,
} ESError;

typedef enum {
    ES_CMD_INVALID,
    ES_CMD_IMP_SERVER_TICKET,
    ES_CMD_IMP_SERVER_TITLE_INIT,
    ES_CMD_IMP_CONTENT_BEGIN,
    ES_CMD_IMP_CONTENT_DATA,
    ES_CMD_IMP_CONTENT_END,
    ES_CMD_IMP_TITLE_DONE,
    ES_CMD_GET_DEVICE_ID,
    ES_CMD_LAUNCH_TITLE,
    ES_CMD_OPEN_CONTENT_FILE,
    ES_CMD_READ_CONTENT_FILE,
    ES_CMD_CLOSE_CONTENT_FILE,
    ES_CMD_LIST_OWNED_TITLES_CNT,
    ES_CMD_LIST_OWNED_TITLES,
    ES_CMD_LIST_TITLES_ON_CARD_CNT,
    ES_CMD_LIST_TITLES_ON_CARD,
    ES_CMD_LIST_TITLE_CONTENTS_CNT,
    ES_CMD_LIST_TITLE_CONTENTS,
    ES_CMD_GET_TICKET_VIEW_CNT,
    ES_CMD_GET_TICKET_VIEWS,
    ES_CMD_GET_TMD_VIEW_SIZE,
    ES_CMD_GET_TMD_VIEW,
    ES_CMD_GET_CONSUMPTION,
    ES_CMD_DELETE_TITLE,
    ES_CMD_DELETE_TICKET,
    ES_CMD_DI_GET_TMD_VIEW_SIZE,
    ES_CMD_DI_GET_TMD_VIEW,
    ES_CMD_DI_GET_TICKET_VIEW,
    ES_CMD_DI_VERIFY,
    ES_CMD_GET_DATA_DIR,
    ES_CMD_GET_DEVICE_CERT,
    ES_CMD_IMP_BOOT,
    ES_CMD_GET_TITLE_ID,
    ES_CMD_SET_UID,
    ES_CMD_DELETE_TITLE_CONTENT,
    ES_CMD_SEEK_CONTENT_FILE,
    ES_CMD_OPEN_TITLE_CONTENT_FILE,
    ES_CMD_SWITCH_MODE,
    ES_CMD_EXP_BACKUP_TITLE_INIT,
    ES_CMD_EXP_CONTENT_BEGIN,
    ES_CMD_EXP_CONTENT_DATA,
    ES_CMD_EXP_CONTENT_END,
    ES_CMD_EXP_TITLE_DONE,
    ES_CMD_IMP_BACKUP_TITLE_INIT,
    ES_CMD_ENCRYPT,
    ES_CMD_DECRYPT,
    ES_CMD_GET_BOOT2_VERSION,
    ES_CMD_IMP_TITLE_CANCEL,
    ES_CMD_SIGN,
    ES_CMD_VERIFY_SIGN,
    ES_CMD_LIST_TMD_CONTENTS_CNT,
    ES_CMD_LIST_TMD_CONTENTS,
    ES_CMD_GET_TMD_SIZE,
    ES_CMD_GET_TMD,
    ES_CMD_LIST_SHARED_CONTENTS_CNT,
    ES_CMD_LIST_SHARED_CONTENTS,
    ES_CMD_DELETE_SHARED_CONTENT,
    ES_CMD_DI_GET_TMD_SIZE,
    ES_CMD_DI_GET_TMD,
    ES_CMD_DI_VERIFY_WITH_TICKET_VIEW,
    ES_CMD_SETUP_STREAM_KEY,
    ES_CMD_DELETE_STREAM_KEY,
    ES_CMD_DELETE_CONTENT,
} ESCommand;

s32 ES_GetDeviceCert(u8* outBuf);
s32 ES_Sign(u8* source, u32 size, u8* sig, u8* cert);

extern int __esFd;

#ifdef __cplusplus
}
#endif
