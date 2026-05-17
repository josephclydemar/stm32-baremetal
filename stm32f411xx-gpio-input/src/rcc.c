#include "rcc.h"

void rcc_gpio_enable(rcc_t *rcc, uint32_t mask)
{
  rcc->ahb1enr |= mask;
}

