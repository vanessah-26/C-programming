#include "io.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_COLORS 256

typedef struct bmp BMP;
BMP *bmp_create(FILE *fin);
void bmp_free(BMP **ppbuf);
void bmp_write(const BMP *pbmp, FILE *fout);
void bmp_reduce_palette(BMP *pbmp);

