#include "stm32f411xx.h"

void nvic_enable_irq(nvic_t *nvic, uint32_t irq_pos, uint32_t irq_priority)
{
  uint32_t ipr_idx = irq_pos >> 2, iser_idx = irq_pos >> 5;
  uint32_t ipr_bit_shift = (irq_pos % 4) * 8, iser_bit_shift = irq_pos % 32;
  nvic->ipr[ipr_idx] &= ~(0xff << ipr_bit_shift);
  nvic->iser[iser_idx] |= ((irq_priority & 0xff) << iser_bit_shift);
}

