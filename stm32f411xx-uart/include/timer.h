#ifndef TIMER_H_
#define TIMER_H_
#include "stm32f411xx.h"

#define TIM2 (tim_t){ .inst = (gptim_t *)TIM2_START }
#define TIM3 (tim_t){ .inst = (gptim_t *)TIM3_START }
#define TIM4 (tim_t){ .inst = (gptim_t *)TIM4_START }
#define TIM5 (tim_t){ .inst = (gptim_t *)TIM5_START }

typedef enum {
  TIMER_CH1 = 0,
  TIMER_CH2 = 1,
  TIMER_CH3 = 2,
  TIMER_CH4 = 3,
} tim_ch_t;

typedef struct {
  volatile gptim_t *inst;
} tim_t;

typedef struct {
  volatile uint32_t psc;
  volatile uint32_t arr;
  volatile uint32_t ccr;
  volatile tim_ch_t ch;
} tim_pwm_cfg_t;

void tim_pwm_init(tim_t t, tim_pwm_cfg_t cfg);
void tim_pwm_write(tim_t t, tim_ch_t ch, uint32_t duty_cycle);

#endif // TIMER_H_

