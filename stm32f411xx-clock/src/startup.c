/* STM32F411xx */
#include "startup.h"


__attribute__((naked, noreturn))
void reset_handler(void)
{
  /* copy contents of .data section from FLASH to SRAM */
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

  sysinit();
  (void)main();
  while (1);
}


void default_handler(void)
{
  while (1);
}


volatile gpio_level_t pa5_state = GPIO_PIN_HIGH;
void stk_handler(void)
{
  gpio_write(PA5, pa5_state);
  pa5_state = !pa5_state;
}

