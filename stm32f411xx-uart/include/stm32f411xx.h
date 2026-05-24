#ifndef STM32F411XX_H_
#define STM32F411XX_H_

#include <stdint.h>
_Static_assert(sizeof(uint8_t) == 1, "Unexpected `uint8_t` size");
_Static_assert(sizeof(uint16_t) == 2, "Unexpected `uint16_t` size");
_Static_assert(sizeof(uint32_t) == 4, "Unexpected `uint32_t` size");
_Static_assert(sizeof(4ul) == 4, "Unexpected `uint32_t` size");


/* CORE PERIPHERALS */
#define STK_START   0xe000e010    /* SysTick address */
typedef struct {
  volatile uint32_t csr;   /* +0x00 */
  volatile uint32_t rvr;   /* +0x04 */
  volatile uint32_t cvr;   /* +0x08 */
  volatile uint32_t calib; /* +0x0c */
} stk_t;


#define NVIC_START      0xe000e100    /* NVIC address */
typedef struct {
  volatile uint32_t iser[8];
  volatile uint32_t icer[8];
  volatile uint32_t ispr[8];
  volatile uint32_t icpr[8];
  volatile uint32_t iabr[8];
  volatile uint32_t ipr[60];
  volatile uint32_t stir;
} nvic_t;


/* EXTERNAL PERIPHERALS */
#define RCC_START       0x40023800    /* RCC address boundary (0x4002 3800 - 0x4002 3BFF) : AHB1 */
typedef struct {
  volatile uint32_t cr;          /* +0x00 */
  volatile uint32_t pllcfgr;     /* +0x04 */
  volatile uint32_t cfgr;        /* +0x08 */
  volatile uint32_t cir;         /* +0x0c */
  volatile uint32_t ahbrstr[2];    /* +0x10, +0x14 */
  volatile uint32_t _reserved1[2]; /* +0x18 (reserved), +0x1c (reserved) */

  volatile uint32_t apbrstr[2];    /* +0x20, +0x24 */
  volatile uint32_t _reserved2[2]; /* +0x28 (reserved), +0x2c (reserved) */

  volatile uint32_t ahbenr[2];     /* +0x30, +0x34 */
  volatile uint32_t _reserved3[2]; /* +0x38 (reserved), +0x3c (reserved) */

  volatile uint32_t apbenr[2];     /* +0x40, +0x44 */
  volatile uint32_t _reserved4[2]; /* +0x48 (reserved), +0x4c (reserved) */

  volatile uint32_t ahblpenr[2];   /* +0x50, +0x54 */
  volatile uint32_t _reserved5[2]; /* +0x58 (reserved), +0x5c (reserved) */

  volatile uint32_t apblpenr[2];   /* +0x60, +0x64 */
  volatile uint32_t _reserved6[2]; /* +0x68 (reserved), +0x6c (reserved) */

  volatile uint32_t bdcr;        /* +0x70 */
  volatile uint32_t csr;         /* +0x74 */
  volatile uint32_t _reserved7[2]; /* +0x78 (reserved), +0x7c (reserved) */

  volatile uint32_t sscgr;       /* +0x80 */
  volatile uint32_t plli2scfgr;  /* +0x84 */
  volatile uint32_t _reserved8; /* +0x88 (reserved) */

  volatile uint32_t dckcfgr;     /* +0x8c */
} rcc_t;


#define PWR_START       0x40007000    /* PWR address boundary (0x4000 7000 - 0x4000 73FF) : APB1 */
typedef struct {
  volatile uint32_t cr;   /* +0x00 */
  volatile uint32_t csr;  /* +0x04 */
} pwr_t;


#define FLASH_INTF_START       0x40023c00    /*  address boundary (0x4002 3C00 - 0x4002 3FFF) : APB1 */
typedef struct {
  volatile uint32_t acr;     /* +0x00 */
  volatile uint32_t keyr;    /* +0x04 */
  volatile uint32_t optkeyr; /* +0x08 */
  volatile uint32_t sr;      /* +0x0c */
  volatile uint32_t cr;      /* +0x10 */
  volatile uint32_t optcr;   /* +0x14 */
} flash_intf_t;


#define GPIOA_START        0x40020000  /* GPIOA address boundary (0x4002 0000 - 0x4002 03FF) : AHB1 */
#define GPIOB_START        0x40020400  /* GPIOB address boundary (0x4002 0400 - 0x4002 07FF) : AHB1 */
/* GPIO registers */
typedef struct {
  volatile uint32_t moder;
  volatile uint32_t otyper;
  volatile uint32_t ospeedr;
  volatile uint32_t pupdr;
  volatile uint32_t idr;
  volatile uint32_t odr;
  volatile uint32_t bsrr;
  volatile uint32_t lckr;
  volatile uint32_t afr[2];
} gpio_t;


#define TIM2_START         0x40000000  /* TIM2 address boundary (0x4000 0000 - 0x4000 03FF) : APB1 */
#define TIM3_START         0x40000400  /* TIM3 address boundary (0x4000 0400 - 0x4000 07FF) : APB1 */
#define TIM4_START         0x40000800  /* TIM4 address boundary (0x4000 0800 - 0x4000 0BFF) : APB1 */
#define TIM5_START         0x40000c00  /* TIM5 boundary address (0x4000 0C00 - 0x4000 0FFF) : APB1 */
typedef struct {
  volatile uint32_t cr1;    /* +0x00 */
  volatile uint32_t cr2;    /* +0x04 */
  volatile uint32_t smcr;   /* +0x08 */
  volatile uint32_t dier;   /* +0x0c */
  volatile uint32_t sr;     /* +0x10 */
  volatile uint32_t egr;    /* +0x14 */
  volatile uint32_t ccmr1;  /* +0x18 */
  volatile uint32_t ccmr2;  /* +0x1c */
  volatile uint32_t ccer;   /* +0x20 */
  volatile uint32_t cnt;    /* +0x24 */
  volatile uint32_t psc;    /* +0x28 */
  volatile uint32_t arr;    /* +0x2c */
  volatile uint32_t _reserved1; /* +0x30 */
  volatile uint32_t ccr[4];   /* +0x34, +0x38, +0x3c, +0x40 */
  volatile uint32_t _reserved2; /* +0x44 */
  volatile uint32_t dcr;    /* +0x48 */
  volatile uint32_t dmar;   /* +0x4c */
  volatile uint32_t tim_or;    /* +0x50 */
} gptim_t;


#define SYSCFG_START       0x40013800 /* SYSCFG address boundary (0x4001 3800 - 0x4001 3BFF) : APB2 */
typedef struct {
  volatile uint32_t memrmp;    /* +0x00 */
  volatile uint32_t pmc;       /* +0x04 */
  volatile uint32_t exticr[4]; /* +0x08, +0x0c, +0x10, +0x14 */
  volatile uint32_t _reserved1[2]; /* +0x18, +0x1c */
  volatile uint32_t cmpcr;     /* +0x20 */
} syscfg_t;


#define EXTI_START         0x40013c00  /* EXTI address boundary (0x4001 3C00 - 0x4001 3FFF) : APB2 */
typedef struct {
  volatile uint32_t imr;    /* +0x00 */
  volatile uint32_t emr;    /* +0x04 */
  volatile uint32_t rtsr;   /* +0x08 */
  volatile uint32_t ftsr;   /* +0x0c */
  volatile uint32_t swier;  /* +0x10 */
  volatile uint32_t pr;     /* +0x14 */
} exti_t;


#define USART1_START         0x40011000  /* USART1 address boundary (0x4001 1000 - 0x4001 13FF) : APB2 */
#define USART2_START         0x40004400  /* USART2 address boundary (0x4000 4400 - 0x4000 47FF) : APB1 */
#define USART6_START         0x40011400  /* USART6 address boundary (0x4001 1400 - 0x4001 17FF) : APB2 */
typedef struct {
  volatile uint32_t sr;    /* +0x00 */
  volatile uint32_t dr;    /* +0x04 */
  volatile uint32_t brr;   /* +0x08 */
  volatile uint32_t cr[3]; /* +0x0c, +0x10, +0x14 */
  volatile uint32_t gtpr;  /* +0x18 */
} usart_t;



int main(void);

#endif // STM32F411XX_H_

