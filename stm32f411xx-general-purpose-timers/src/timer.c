#include "stm32f411xx.h"
#include "timer.h"

#define TIMx_CR1_CEN          (1ul)
#define TIMx_CR1_ARPE         (1ul << 7)

#define TIMx_EGR_UG           (1ul)


void timer_init(tim_t t, tim_base_cfg_t cfg)
{
  volatile gptim_t *tim = t.inst;
  /* set timing */
  tim->psc = cfg.psc;
  tim->arr = cfg.arr;

  /* set count to zero */
  tim->cnt = 0;

  /* update registers */
  tim->egr = TIMx_EGR_UG;
}

void timer_start(tim_t t)
{
  /* enable counter */
  volatile gptim_t *tim = t.inst;
  tim->cr1 |= TIMx_CR1_CEN;
}

void timer_pwm_channel_init(tim_t t, tim_pwm_ch_cfg_t cfg)
{
  volatile gptim_t *tim = t.inst;
  /* select CCMR register */
  uint32_t channel= cfg.ch;
  uint32_t shift;
  volatile uint32_t *ccmr;
  if (channel< 2) {
    ccmr = &tim->ccmr1;
    shift = channel* 8;
  } else {
    ccmr = &tim->ccmr2;
    shift = (channel- 2) * 8;
  }

  /* capture/compare CCxS = 00 (output) */
  *ccmr &= ~(0x3ul << shift);

  /* OCxPE = 1 */
  *ccmr |= (1ul << (shift + 3));

  /* PWM mode 1 (OCxM = 110) */
  *ccmr &= ~(0x7ul << (shift + 4));
  *ccmr |= (0x6ul << (shift + 4));

  /* set CCRx */
  tim->ccr[channel] = cfg.ccr;

  /* enable channel */
  // tim->ccer &= ~(0xFul << (channel* 4));
  tim->ccer |= (1ul << (channel* 4));
}

void timer_pwm_write(tim_t t, tim_ch_t ch, uint32_t duty_cycle)
{
  volatile gptim_t *tim = t.inst;
  if (duty_cycle >= tim->arr) duty_cycle = tim->arr;
  tim->ccr[ch] = duty_cycle;
}

void timer_input_capture_channel_init(tim_t t, tim_ch_t ch)
{
  volatile gptim_t *tim = t.inst;
  /* select CCMR register */
  uint32_t channel = ch;
  uint32_t shift;
  volatile uint32_t *ccmr;
  if (channel < 2) {
    ccmr = &tim->ccmr1;
    shift = channel * 8;
  } else {
    ccmr = &tim->ccmr2;
    shift = (channel - 2) * 8;
  }
  /* capture/compare CCxS = 01 (input) */
  *ccmr &= ~(3ul << shift);
  *ccmr |= (1ul << shift);

  // capture event prescaler (none)
  *ccmr &= ~(3ul << (shift + 2));

  // edge noise filter
  *ccmr &= ~(15ul << (shift + 4));
  // *ccmr |= (2ul << (shift + 4));

  nvic_enable_irq((nvic_t *)NVIC_ADDR, 29, 36);
  /* enable input capture interrupt */
  tim->dier |= (1ul << (channel + 1));

  /* enable channel */
  tim->ccer |= (1ul << (channel * 4));
}

