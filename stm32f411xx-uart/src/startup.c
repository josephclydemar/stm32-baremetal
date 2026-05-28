/* STM32F411xx */
#include "startup.h"
#include "usart.h"

void nmi_handler(void)            __attribute__((weak, alias("default_handler")));
void hardfault_handler(void)      __attribute__((weak, alias("default_handler")));
void memmanage_handler(void)      __attribute__((weak, alias("default_handler")));
void busfault_handler(void)       __attribute__((weak, alias("default_handler")));
void usagefault_handler(void)     __attribute__((weak, alias("default_handler")));
void svc_handler(void)            __attribute__((weak, alias("default_handler")));
void debugmon_handler(void)       __attribute__((weak, alias("default_handler")));
void pendsv_handler(void)         __attribute__((weak, alias("default_handler")));
void stk_handler(void)            __attribute__((weak, alias("default_handler")));


void default_handler(void)
{
  while (1);
}

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

void usart2_handler(void) {
  usart_t *usart = USART2;
  char buf[12];
  buf[0] = '[';
  buf[1] = 'h';
  buf[2] = 'e';
  buf[3] = 'l';
  buf[4] = 'l';
  buf[5] = 'o';
  buf[6] = ':';
  buf[7] = ' ';
  buf[8] = (char)(usart->dr & 0xff);
  buf[9] = ']';
  buf[10] = '\r';
  buf[11] = '\n';
  usart_send(usart, buf, 12);
}

