#ifndef COMMON_H_
#define COMMON_H_

// typedef unsigned char uint8_t;
// typedef unsigned short uint16_t;
// typedef unsigned long uint32_t;

#include <stdint.h>
_Static_assert(sizeof(uint8_t) == 1, "Unexpected `uint8_t` size");
_Static_assert(sizeof(uint16_t) == 2, "Unexpected `uint16_t` size");
_Static_assert(sizeof(uint32_t) == 4, "Unexpected `uint32_t` size");

#define NULL                ((uint32_t *)0)

int main(void);

#endif // COMMON_H_

