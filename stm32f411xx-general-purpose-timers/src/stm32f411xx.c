#include "stm32f411xx.h"

void stk_init(stk_t *systim, uint32_t ticks)
{
  systim->rvr = ticks - 1;
  systim->cvr = 0;
  systim->csr |= 7ul;
}

void nvic_enable_irq(nvic_t *nvic, uint32_t irq_pos, uint8_t irq_priority)
{
  uint32_t ipr_idx = irq_pos >> 2, iser_idx = irq_pos >> 5;
  uint32_t ipr_bit_shift = (irq_pos % 4) * 8, iser_bit_shift = irq_pos % 32;
  nvic->ipr[ipr_idx] &= ~(0xfful << ipr_bit_shift);
  nvic->ipr[ipr_idx] |= (((uint32_t)irq_priority) << ipr_bit_shift);
  nvic->iser[iser_idx] |= (1ul << iser_bit_shift);
}

