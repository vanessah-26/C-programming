#include "bitwriter.h"

#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    BitWriter *writer = (BitWriter *) malloc(sizeof(BitWriter));

    if (writer == NULL) {
        return NULL;
    }

    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        free(writer);
        return NULL;
    }

    writer->underlying_stream = file;
    writer->byte = 0;
    writer->bit_position = 0;

    return writer;
}

void bit_write_close(BitWriter **pbuf) {
    if (*pbuf != NULL) {
        if ((*pbuf)->bit_position > 0) {
            int res = fputc((*pbuf)->byte, (*pbuf)->underlying_stream);
            if (res == EOF) {
                printf("Error writing byte to the underlying stream\n");
                exit(1);
            }
            (*pbuf)->bit_position = 0;
            (*pbuf)->byte = 0;
        }

        if (fclose((*pbuf)->underlying_stream) != 0) {
            printf("Error closing underlying stream\n");
            exit(1);
        }

        free(*pbuf);
        *pbuf = NULL;
    }
}

void bit_write_bit(BitWriter *buf, uint8_t x) {
    if (buf->bit_position > 7) {
        int res = fputc(buf->byte, buf->underlying_stream);
        if (res == EOF) {
            printf("Error writing byte to the underlying stream\n");
            exit(1);
        }
        buf->byte = 0;
        buf->bit_position = 0;
    }

    buf->byte |= (x & 1) << buf->bit_position;
    buf->bit_position += 1;
}

void bit_write_uint8(BitWriter *buf, uint8_t x) {
    for (int i = 0; i < 8; i++) {
        uint8_t bit = (x >> i) & 1;
        bit_write_bit(buf, bit);
    }
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i < 16; i++) {
        uint16_t bit = (x >> i) & 1;
        bit_write_bit(buf, (uint8_t) bit);
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i < 32; i++) {
        uint32_t bit = (x >> i) & 1;
        bit_write_bit(buf, (uint8_t) bit);
    }
}
