#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void read_uint8(FILE *fin, uint8_t *px) {
    int result = fgetc(fin);

    if (result == EOF) {
        fprintf(stderr, "unexpected end of file.\n");
        exit(EXIT_FAILURE); //built in stdlib, use this instead of return t/f cuz this is void
    }

    *px = (uint8_t) result;
}

void read_uint16(FILE *fin, uint16_t *px) {
    uint8_t b1, b2;

    read_uint8(fin, &b1);
    read_uint8(fin, &b2);

    *px = (uint16_t) ((b2 << 8) | b1);
}

void read_uint32(FILE *fin, uint32_t *px) {
    uint16_t b1, b2;

    read_uint16(fin, &b1);
    read_uint16(fin, &b2);

    *px = (uint32_t) ((b2 << 16) | b1);
}

//write

void write_uint8(FILE *fout, uint8_t x) {
    int result = fputc(x, fout);

    if (result == EOF) {
        fprintf(stderr, "unable to write file\n");
        exit(EXIT_FAILURE);
    }
}

void write_uint16(FILE *fout, uint16_t x) {
    uint8_t b1, b2;
    b1 = x & 0xFF;
    b2 = (x >> 8) & 0xFF;

    write_uint8(fout, b1);
    write_uint8(fout, b2);
}

void write_uint32(FILE *fout, uint32_t x) {
    uint16_t b1 = x & 0xFFFF;
    uint16_t b2 = (x >> 16) & 0xFFFF;

    write_uint16(fout, b1);
    write_uint16(fout, b2);
}
