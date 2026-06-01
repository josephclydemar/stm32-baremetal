#ifndef TIMER_H_
#define TIMER_H_
#include "stm32f411xx.h"

#define TIM2 (tim_t){ .inst = (gptim_t *)TIM2_ADDR }
#define TIM3 (tim_t){ .inst = (gptim_t *)TIM3_ADDR }
#define TIM4 (tim_t){ .inst = (gptim_t *)TIM4_ADDR }
#define TIM5 (tim_t){ .inst = (gptim_t *)TIM5_ADDR }

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
} tim_base_cfg_t;

typedef struct {
  volatile uint32_t ccr;
  volatile tim_ch_t ch;
} tim_pwm_ch_cfg_t;

void timer_init(tim_t t, tim_base_cfg_t cfg);
void timer_start(tim_t t);
void timer_pwm_channel_init(tim_t t, tim_pwm_ch_cfg_t cfg);
void timer_pwm_write(tim_t t, tim_ch_t ch, uint32_t duty_cycle);
void timer_input_capture_channel_init(tim_t t, tim_ch_t ch);

#endif // TIMER_H_

