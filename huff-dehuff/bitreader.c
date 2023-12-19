#include "bitreader.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
} BitReader;

//bit_read_open

BitReader *bit_read_open(const char *filename) {
    BitReader *reader = (BitReader *) malloc(sizeof(BitReader));

    //check if mem alloc fail
    if (reader == NULL) {
        return NULL;
    }

    //open filename for reading and save to *file
    FILE *file = fopen(filename, "rb");

    //check if opening file success
    if (file == NULL) {
        free(reader);
        return NULL;
    }

    //store the file in BitReader field underlying_str
    reader->underlying_stream = file;

    //clear byte filed
    reader->byte = 0;

    //set bit_pos field to 8
    reader->bit_position = 8;

    return reader;
}

//bit_read_close
void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        int res = fclose((*pbuf)->underlying_stream);

        if (res != 0) {
            printf("Error closing the underlying stream\n");
            exit(1);
        }

        //free BitReader obj
        free(*pbuf);

        *pbuf = NULL;
    }
}

//bit_read_bit

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        int byte = fgetc(buf->underlying_stream);

        if (byte == EOF) {
            printf("Error reading bit from the underlying stream\n");
            exit(1);
        }

        buf->bit_position = 0;
        //update byte field
        buf->byte = (uint8_t) byte;
    }
    //get the bit numbered bit_position from the byte
    uint8_t bit = (buf->byte >> buf->bit_position) & 1;

    buf->bit_position += 1;

    return bit;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0x00;
    for (int i = 0; i < 8; i++) {
        //read a bit b from the underlying_stream
        uint8_t b = bit_read_bit(buf);
        //set bit i of byte to the value b
        byte |= (b << i);
    }
    return byte;
}

//bit_read_uint16

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t word = 0x0000;
    for (int i = 0; i < 16; i++) {
        uint8_t b = bit_read_bit(buf); //uint8 since reading individual bits
        word |= ((uint16_t) b << i);
    }
    return word;
}

//bit_read_uint32

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t word = 0x00000000;
    for (int i = 0; i < 32; i++) {
        uint8_t b = bit_read_bit(buf);
        word |= ((uint32_t) b << i);
    }
    return word;
}
