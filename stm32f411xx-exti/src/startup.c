/* STM32F411xx */
#include "startup.h"
#include "gpio.h"


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


void default_handler(void)
{
  while (1);
}


volatile uint32_t s_ticks = 0, lpress_ticks = 0;
void stk_handler(void)
{
  ++s_ticks;
}


volatile gpio_level_t led_state = GPIO_PIN_LOW;
void exti4_handler(void)
{
  exti_t *exti = (exti_t *)EXTI_START;
  exti->pr = (1 << 4);

  if ((s_ticks - lpress_ticks) < 100) return;
  lpress_ticks = s_ticks;

  gpio_write(PA7, led_state);
  gpio_write(PB6, !led_state);
  led_state = !led_state;
}

