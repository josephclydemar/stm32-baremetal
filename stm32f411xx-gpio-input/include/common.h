#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

_Static_assert(sizeof(uint8_t) == 1, "Unexpected `uint8_t` size");
_Static_assert(sizeof(uint16_t) == 2, "Unexpected `uint16_t` size");
_Static_assert(sizeof(uint32_t) == 4, "Unexpected `uint32_t` size");


void main(void);

#endif // COMMON_H_

