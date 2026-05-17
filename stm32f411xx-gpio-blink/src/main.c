/* STM32F411xx */
#include "common.h"

/* RCC address boundary (0x4002 3800 - 0x4002 3BFF) */
#define RCC_START       0x40023800ul
#define RCC_AHB1ENR     ((volatile uint32_t *)(RCC_START + 0x30ul))

/* GPIOA address boundary (0x4002 0000 - 0x4002 03FF) */
#define GPIOA_START     0x40020000ul
#define GPIOA_MODER     ((volatile uint32_t *)(GPIOA_START + 0x00ul))
#define GPIOA_BSRR      ((volatile uint32_t *)(GPIOA_START + 0x18ul))

/* Reset and Clock Control (RCC) Peripheral */
typedef struct {
  volatile uint32_t cr; /* +0x00 */
  volatile uint32_t pllcfgr; /* +0x04 */
  volatile uint32_t cfgr; /* +0x08 */
  volatile uint32_t cir; /* +0x0c */
  volatile uint32_t ahb1rstr; /* +0x10 */
  volatile uint32_t ahb2rstr; /* +0x14 */
  volatile uint32_t reserved1, reserved2; /* +0x18 (reserved), +0x1c (reserved) */
  volatile uint32_t apb1rstr; /* +0x20 */
  volatile uint32_t apb2rstr; /* +0x24 */
  volatile uint32_t reserved3, reserved4; /* +0x28 (reserved), +0x2c (reserved) */
  volatile uint32_t ahb1enr; /* +0x30 AHB1ENR */
  volatile uint32_t ahb2enr; /* +0x34 */
} rcc_t; /* registers still incomplete */

typedef struct {
  volatile uint32_t moder;
  volatile uint32_t otyper;
  volatile uint32_t ospeedr;
  volatile uint32_t pupdr;
  volatile uint32_t idr;
  volatile uint32_t odr;
  volatile uint32_t bsrr;
  volatile uint32_t lckr;
  volatile uint32_t afrl;
  volatile uint32_t afrh;
} gpio_t;

int main(void)
{
  rcc_t *rcc = (rcc_t *)RCC_START;
  rcc->ahb1enr |= 0x1; /* RCC_AHB1ENR |= 0x1 : Turn on the clock for GPIOA */

  gpio_t *gpio_a = (gpio_t *)GPIOA_START;
  /* Set PA5 to output mode */
  gpio_a->moder &= ~(0x3 << 0xa);
  gpio_a->moder |= (0x1 << 0xa);

  while (1) {
    /* PA5 slow blink */
    for (int idx = 0; idx < 10; ++idx) {
      gpio_a->bsrr = (0x1 << 0x5);
      for (volatile uint32_t i = 0; i < 200000; i++);
      gpio_a->bsrr = (0x1 << 0x15);
      for (volatile uint32_t i = 0; i < 200000; i++);
    }

    /* PA5 fast blink */
    for (int idx = 0; idx < 40; ++idx) {
      gpio_a->bsrr = (0x1 << 0x5);
      for (volatile uint32_t i = 0; i < 50000; i++);
      gpio_a->bsrr = (0x1 << 0x15);
      for (volatile uint32_t i = 0; i < 50000; i++);
    }
  }
}


