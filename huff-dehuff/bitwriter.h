#include <inttypes.h>

typedef struct BitWriter BitWriter;

BitWriter *bit_write_open(const char *filename);
void bit_write_close(BitWriter **pbuf);
void bit_write_bit(BitWriter *buf, uint8_t bit);
void bit_write_uint16(BitWriter *buf, uint16_t x);
void bit_write_uint32(BitWriter *buf, uint32_t x);
void bit_write_uint8(BitWriter *buf, uint8_t byte);

#endif
