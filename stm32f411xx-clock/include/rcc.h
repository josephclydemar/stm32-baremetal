#ifndef RCC_H_
#define RCC_H_

#include "stm32f411xx.h"

/* GPIO */
#define RCC_GPIOA      (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_START)->ahbenr[0]), .mask = (0x1u << 0x0) }
#define RCC_GPIOB      (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_START)->ahbenr[0]), .mask = (0x1u << 0x1) }

/* TIMERS */
#define RCC_TIM2       (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_START)->apbenr[0]), .mask = (0x1u << 0x0) }
#define RCC_TIM3       (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_START)->apbenr[0]), .mask = (0x1u << 0x1) }
#define RCC_TIM4       (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_START)->apbenr[0]), .mask = (0x1u << 0x2) }
#define RCC_TIM5       (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_START)->apbenr[0]), .mask = (0x1u << 0x3) }

#define RCC_SYSCFG    (rcc_periph_t){ .reg = &(((volatile rcc_t *)RCC_START)->apbenr[1]), .mask = (0x1u << 0xe) }

typedef struct {
    volatile uint32_t *reg;  // pointer to enable register
    volatile uint32_t mask;            // bit mask
} rcc_periph_t;

void rcc_pll_config(void);
void rcc_periph_enable(rcc_periph_t p);

#endif // RCC_H_

