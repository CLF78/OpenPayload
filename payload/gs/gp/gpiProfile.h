#include <common/Common.h>
#include <gs/hashtable.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    HashTable profileHashTable;
    int num;
    int numBuddies;
} GPIProfileList;

#ifdef __cplusplus
}
#endif
