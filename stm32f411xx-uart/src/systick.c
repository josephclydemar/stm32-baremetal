#include "systick.h"

void stk_init(stk_t *systim, uint32_t ticks)
{
  systim->rvr = ticks - 1;
  systim->cvr = 0;
  systim->csr |= 7ul;
}
