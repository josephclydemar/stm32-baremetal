#include "util.h"

uint32_t u32word2hex_rev_encode(uint32_t n, char *str_buf)
{
  uint32_t str_idx = 0;
  char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  for (uint32_t idx = 0; idx < 8; ++idx) {
    str_buf[idx] = '0';
  }

  if (n == 0) return 1;
  while (n > 0) {
    str_buf[7 - str_idx] = hex[n & 0xf];
    ++str_idx;
    n = n >> 4;
  }
  return str_idx + 1;
}

