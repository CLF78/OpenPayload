#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SC_LANG_JAPANESE,
    SC_LANG_ENGLISH,
    SC_LANG_GERMAN,
    SC_LANG_FRENCH,
    SC_LANG_SPANISH,
    SC_LANG_ITALIAN,
    SC_LANG_DUTCH,
    SC_LANG_SIMP_CHINESE,
    SC_LANG_TRAD_CHINESE,
    SC_LANG_KOREAN,
} SCLanguage;

u8 SCGetLanguage();
char* SCGetProductCode();

#ifdef __cplusplus
}
#endif
