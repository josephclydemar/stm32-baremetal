#include "timer.h"

#define TIMx_CR1_CEN            (1ul)
#define TIMx_CR1_ARPE           (1ul << 7)

#define TIMx_EGR_UG             (1ul)



void tim_pwm_init(tim_t t, tim_pwm_cfg_t cfg)
{
    volatile gptim_t *tim = t.inst;
    uint32_t ch = cfg.ch;
    /* Select CCMR register */
    volatile uint32_t *ccmr;
    uint32_t shift;

    /* Enable ARR preload */
    tim->cr1 |= TIMx_CR1_ARPE;

    if (ch < 2) {
      ccmr = &tim->ccmr1;
      shift = ch * 8;
    } else {
      ccmr = &tim->ccmr2;
      shift = (ch - 2) * 8;
    }

    /* CCxS = 00 (output) */
    *ccmr &= ~(0x3ul << shift);

    /* OCxPE = 1 */
    *ccmr |= (1ul << (shift + 3));

    /* PWM mode 1 (OCxM = 110) */
    *ccmr &= ~(0x7ul << (shift + 4));
    *ccmr |= (0x6ul << (shift + 4));

    /* Set timing */
    tim->psc = cfg.psc;
    tim->arr = cfg.arr;

    /* Set CCRx */
    tim->ccr[ch] = cfg.ccr;

    /* Set count to zero */
    tim->cnt = 0;

    /* Enable channel */
    tim->ccer &= ~(0xFul << (ch * 4));
    tim->ccer |= (1ul << (ch * 4));

    /* Update registers */
    tim->egr = TIMx_EGR_UG;
    /* Enable counter */
    tim->cr1 |= TIMx_CR1_CEN;
}

void tim_pwm_write(tim_t t, tim_ch_t ch, uint32_t duty_cycle)
{
  volatile gptim_t *tim = t.inst;
  if (duty_cycle >= tim->arr) {
    duty_cycle = tim->arr - 1;
  }
  tim->ccr[ch] = duty_cycle;
}

