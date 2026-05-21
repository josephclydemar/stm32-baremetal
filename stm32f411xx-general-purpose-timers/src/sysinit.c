#include "systick.h"
#include "rcc.h"

void sysinit(void)
{
  rcc_pll_config();
  stk_init((stk_t *)STK_ADDR, 8000000);
}
