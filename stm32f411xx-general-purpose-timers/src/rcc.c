#include "rcc.h"

void rcc_periph_enable(rcc_periph_t p)
{
  *p.reg |= p.mask;
}

