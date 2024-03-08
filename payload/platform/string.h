#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* destination, const void* source, size_t size);
void* memset(void* ptr, int value, size_t num);

int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t num);
char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t num);
char* strstr(char* str1, const char* str2);
size_t strlen(const char* str);
u32 strtoul(const char* str, char** endptr, int base);

#define strshift(str, str2) (str) += sizeof((str2)) - 1
#define strstartw(str, str2) (strncmp((str), (str2), sizeof((str2)) - 1) == 0)

#ifdef __cplusplus
}
#endif
