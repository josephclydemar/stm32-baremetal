#ifndef RCC_H_
#define RCC_H_

#include "common.h"

/* RCC address boundary (0x4002 3800 - 0x4002 3BFF) : AHB1 */
#define RCC_START       0x40023800ul
#define RCC_AHB1ENR     ((volatile uint32_t *)(RCC_START + 0x30ul))

#define RCC_GPIOA_MASK            (0x1)
#define RCC_GPIOB_MASK            (0x1 << 0x1)
#define RCC_GPIOC_MASK            (0x1 << 0x2)
#define RCC_GPIOD_MASK            (0x1 << 0x3)
#define RCC_GPIOE_MASK            (0x1 << 0x4)

#define RCC_GPIOA_MASK_INV        ~(0x1)
#define RCC_GPIOB_MASK_INV        ~(0x1 << 0x1)
#define RCC_GPIOC_MASK_INV        ~(0x1 << 0x2)
#define RCC_GPIOD_MASK_INV        ~(0x1 << 0x3)
#define RCC_GPIOE_MASK_INV        ~(0x1 << 0x4)

#define RCC_TIM2_MASK            (0x1)
#define RCC_TIM3_MASK            (0x1 << 0x1)
#define RCC_TIM4_MASK            (0x1 << 0x2)
#define RCC_TIM5_MASK            (0x1 << 0x3)


/* RCC registers */
typedef struct {
  volatile uint32_t cr;          /* +0x00 */
  volatile uint32_t pllcfgr;     /* +0x04 */
  volatile uint32_t cfgr;        /* +0x08 */
  volatile uint32_t cir;         /* +0x0c */
  volatile uint32_t ahb1rstr;    /* +0x10 */
  volatile uint32_t ahb2rstr;    /* +0x14 */
  volatile uint32_t _reserved1[2]; /* +0x18 (reserved), +0x1c (reserved) */

  volatile uint32_t apb1rstr;    /* +0x20 */
  volatile uint32_t apb2rstr;    /* +0x24 */
  volatile uint32_t _reserved2[2]; /* +0x28 (reserved), +0x2c (reserved) */

  volatile uint32_t ahb1enr;     /* +0x30 AHB1ENR */
  volatile uint32_t ahb2enr;     /* +0x34 */
  volatile uint32_t _reserved3[2]; /* +0x38 (reserved), +0x3c (reserved) */

  volatile uint32_t apb1enr;     /* +0x40 */
  volatile uint32_t apb2enr;     /* +0x44 */
  volatile uint32_t _reserved4[2]; /* +0x48 (reserved), +0x4c (reserved) */

  volatile uint32_t ahb1lpenr;   /* +0x50 */
  volatile uint32_t ahb2lpenr;   /* +0x54 */
  volatile uint32_t _reserved5[2]; /* +0x58 (reserved), +0x5c (reserved) */

  volatile uint32_t apb1lpenr;   /* +0x60 */
  volatile uint32_t apb2lpenr;   /* +0x64 */
  volatile uint32_t _reserved6[2]; /* +0x68 (reserved), +0x6c (reserved) */

  volatile uint32_t bdcr;        /* +0x70 */
  volatile uint32_t csr;         /* +0x74 */
  volatile uint32_t _reserved7[2]; /* +0x78 (reserved), +0x7c (reserved) */

  volatile uint32_t sscgr;       /* +0x80 */
  volatile uint32_t plli2scfgr;  /* +0x84 */
  volatile uint32_t _reserved8; /* +0x88 (reserved) */

  volatile uint32_t dckcfgr;     /* +0x8c */
} rcc_t; /* registers still incomplete */

void rcc_gpio_enable(rcc_t *rcc, uint32_t mask);

#endif // RCC_H_

