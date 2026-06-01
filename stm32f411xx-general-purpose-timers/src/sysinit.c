#include "stm32f411xx.h"
#include "rcc.h"
// #include "usart.h"

void sysinit(void)
{
  rcc_pll_config();
  stk_init((stk_t *)STK_ADDR, 25000);
}
