#include <common/Common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float x, y;
} VEC2;

typedef struct {
    float x, y, z;
} VEC3;

typedef struct {
    float x, y, z, w;
} QUAT;

typedef struct {
    s16 x, y, z;
} S16VEC;

typedef float MTX33[3][3];
typedef float MTX34[3][4];
typedef float MTX44[4][4];

#ifdef __cplusplus
}
#endif
