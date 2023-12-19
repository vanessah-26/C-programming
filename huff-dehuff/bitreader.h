#include <inttypes.h>
#include <stdbool.h>

typedef struct BitReader BitReader;

BitReader *bit_read_open(const char *filename);
void bit_read_close(BitReader **pbuf);
uint32_t bit_read_uint32(BitReader *buf);
uint16_t bit_read_uint16(BitReader *buf);
uint8_t bit_read_uint8(BitReader *buf);
uint8_t bit_read_bit(BitReader *buf);

#endif
