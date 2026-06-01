#ifndef RCC_H_
#define RCC_H_

#include "stm32f411xx.h"


/* Clock Control Register */
#define RCC_CR_HSION     (1ul)
#define RCC_CR_HSIRDY    (1ul << 1)
#define RCC_CR_HSEON     (1ul << 16)
#define RCC_CR_HSERDY    (1ul << 17)
#define RCC_CR_PLLON     (1ul << 24)
#define RCC_CR_PLLRDY    (1ul << 25)


/* PLL Configuration Register */
#define RCC_PLLCFGR_PLLP_DIV2      (0ul << 16)
#define RCC_PLLCFGR_PLLP_DIV4      (1ul << 16)
#define RCC_PLLCFGR_PLLP_DIV6      (2ul << 16)
#define RCC_PLLCFGR_PLLP_DIV8      (3ul << 16)

#define RCC_PLLCFGR_PLLSRC      (1ul << 22)


/* Clock Configuration Register */
#define RCC_CFGR_SW_HSI            (0ul)
#define RCC_CFGR_SW_HSE            (1ul)
#define RCC_CFGR_SW_PLL            (2ul)
#define RCC_CFGR_SW_NOTALLOWED     (3ul)

#define RCC_CFGR_SWS_HSI               (0ul << 2)
#define RCC_CFGR_SWS_HSE               (1ul << 2)
#define RCC_CFGR_SWS_PLL               (2ul << 2)
#define RCC_CFGR_SWS_NOTAPPLICABLE     (3ul << 2)

#define RCC_CFGR_HPRE_NODIV     (0ul << 4)
#define RCC_CFGR_HPRE_DIV2      (8ul << 4)
#define RCC_CFGR_HPRE_DIV512    (15ul << 4)

#define RCC_CFGR_PPRE1_NODIV   (0ul << 10)
#define RCC_CFGR_PPRE1_DIV2    (4ul << 10)
#define RCC_CFGR_PPRE1_DIV4    (5ul << 10)
#define RCC_CFGR_PPRE1_DIV8    (6ul << 10)
#define RCC_CFGR_PPRE1_DIV16   (7ul << 10)

#define RCC_CFGR_PPRE2_NODIV   (0ul << 13)
#define RCC_CFGR_PPRE2_DIV2    (4ul << 13)
#define RCC_CFGR_PPRE2_DIV4    (5ul << 13)
#define RCC_CFGR_PPRE2_DIV8    (6ul << 13)
#define RCC_CFGR_PPRE2_DIV16   (7ul << 13)


/* AHB1 Clock Enable Register */
#define RCC_AHB1ENR_GPIOAEN       (1ul)
#define RCC_AHB1ENR_GPIOBEN       (1ul << 1)
#define RCC_AHB1ENR_GPIOCEN       (1ul << 2)
#define RCC_AHB1ENR_GPIODEN       (1ul << 3)
#define RCC_AHB1ENR_GPIOEEN       (1ul << 4)
#define RCC_AHB1ENR_GPIOHEN       (1ul << 7)
#define RCC_AHB1ENR_CRCEN         (1ul << 12)
#define RCC_AHB1ENR_DMA1EN        (1ul << 21)
#define RCC_AHB1ENR_DMA2EN        (1ul << 22)


/* APB1 Clock Enable Register */
#define RCC_APB1ENR_TIM2EN       (1ul)
#define RCC_APB1ENR_TIM3EN       (1ul << 1)
#define RCC_APB1ENR_TIM4EN       (1ul << 2)
#define RCC_APB1ENR_TIM5EN       (1ul << 3)
#define RCC_APB1ENR_USART2EN     (1ul << 17)
#define RCC_APB1ENR_PWREN        (1ul << 28)


/* APB2 Clock Enable Register */
#define RCC_APB2ENR_SYSCFGEN       (1ul << 14)



#define RCC_GPIOA      (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->ahbenr[0]), .mask = RCC_AHB1ENR_GPIOAEN }
#define RCC_GPIOB      (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->ahbenr[0]), .mask = RCC_AHB1ENR_GPIOBEN }
#define RCC_TIM2       (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->apbenr[0]), .mask = RCC_APB1ENR_TIM2EN }
#define RCC_TIM3       (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->apbenr[0]), .mask = RCC_APB1ENR_TIM3EN }
#define RCC_TIM4       (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->apbenr[0]), .mask = RCC_APB1ENR_TIM4EN }
#define RCC_TIM5       (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->apbenr[0]), .mask = RCC_APB1ENR_TIM5EN }
#define RCC_USART1     (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->apbenr[1]), .mask = (1u << 4) }
#define RCC_USART2     (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->apbenr[0]), .mask = (1u << 17) }
#define RCC_USART6     (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->apbenr[1]), .mask = (1u << 5) }
#define RCC_SYSCFG    (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_ADDR)->apbenr[1]), .mask = RCC_APB2ENR_SYSCFGEN }



typedef struct {
    volatile uint32_t *reg;  // pointer to enable register
    volatile uint32_t mask;            // bit mask
} rcc_periph_t;

void rcc_pll_config(void);
void rcc_periph_enable(rcc_periph_t p);

#endif // RCC_H_

