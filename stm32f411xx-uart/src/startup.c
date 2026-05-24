/* STM32F411xx */
#include "stm32f411xx.h"
#include "gpio.h"

extern uint32_t _estack, _sidata, _sdata, _edata, _sbss, _ebss;

/* Forward declarations */
void reset_handler(void);
void default_handler(void);
void stk_handler(void);

/* Weak aliases (all unimplemented interrupts go here) */
void nmi_handler(void)            __attribute__((weak, alias("default_handler")));
void hardfault_handler(void)      __attribute__((weak, alias("default_handler")));
void memmanage_handler(void)      __attribute__((weak, alias("default_handler")));
void busfault_handler(void)       __attribute__((weak, alias("default_handler")));
void usagefault_handler(void)     __attribute__((weak, alias("default_handler")));
void svc_handler(void)            __attribute__((weak, alias("default_handler")));
void debugmon_handler(void)       __attribute__((weak, alias("default_handler")));
void pendsv_handler(void)         __attribute__((weak, alias("default_handler")));

/* Vector table */
__attribute__((section(".isr_vector")))
void (*const vector_table[])(void) = {
  (void (*)(void))(&_estack),  // 0: Initial stack pointer
  reset_handler,               // 1: Reset
  nmi_handler,                 // 2
  hardfault_handler,           // 3
  memmanage_handler,           // 4
  busfault_handler,            // 5
  usagefault_handler,          // 6
  0, 0, 0, 0,                 // 7–10 reserved
  svc_handler,                 // 11
  debugmon_handler,            // 12
  0,                           // 13 reserved
  pendsv_handler,              // 14
  stk_handler,             // 15

  /* ---- STM32F411 specific interrupts (partial) ---- */
  default_handler, // 16: WWDG
  default_handler, // 17: PVD
  default_handler, // 18: TAMP_STAMP
  default_handler, // 19: RTC_WKUP
  default_handler, // 20: FLASH
  default_handler, // 21: RCC
  default_handler, // 22: EXTI0
  default_handler, // 23: EXTI1
  default_handler, // 24: EXTI2
  default_handler, // 25: EXTI3
  default_handler, // 26: EXTI4
  default_handler, // 27: DMA1_Stream0
  default_handler, // 28: DMA1_Stream1
  default_handler, // 29: DMA1_Stream2
  default_handler, // 30: DMA1_Stream3
  default_handler, // 31: DMA1_Stream4
  default_handler, // 32: DMA1_Stream5
  default_handler, // 33: DMA1_Stream6
  default_handler, // 34: ADC
  default_handler, // 35: EXTI9_5
  // ... (continues for all IRQs)
};

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

volatile uint32_t s_ticks = 0;
void stk_handler(void)
{
  ++s_ticks;
}

