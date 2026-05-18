/* STM32F411xx */
#include "startup.h"

__attribute__((naked, noreturn))
void reset_handler(void)
{
  /* copy initialized data from FLASH to SRAM */
  uint32_t *src = &_sidata, *dst = &_sdata;
  while (dst < &_edata) {
    *dst = *src;
    ++dst;
    ++src;
  }

  /* zero the .bss section */
  uint32_t *bss = &_sbss;
  while (bss < &_ebss) {
    *bss = 0;
    ++bss;
  }

  (void)main();

  while (1);
}

volatile uint32_t s_ticks = 0;
void stk_handler(void)
{
  ++s_ticks;
}

void default_handler(void)
{
  while (1);
}


