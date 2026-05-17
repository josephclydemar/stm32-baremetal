#include "rcc.h"

void rcc_periph_enable(rcc_periph_t p)
{
  *p.reg |= p.mask;
}

void rcc_pll_config(void)
{
  rcc_t *rcc = (rcc_t *)RCC_START;
  pwr_t *pwr = (pwr_t *)PWR_START;
  flash_intf_t *flash = (flash_intf_t *)FLASH_INTF_START;

  rcc->cr |= (1ul << 16); /* Set HSEON bit */
  while (!(rcc->cr & (1ul << 17))); /* Wait for HSERDY bit to be set */

  /* Voltage scaling configuration */
  rcc->apbenr[0] |= (1ul << 28); /* Set PWREN bit */
  pwr->cr |= (3ul << 14); /* Set VOS bit (Scale 1) */

  /* Flash configuration for caching, prefetching, wait state */
  flash->acr |= (7ul << 8); /* Set the bits ICEN, DCEN, PRFTEN */
  flash->acr &= ~(0xful); /* Clear LATENCY */
  flash->acr |= 5ul;      /* Set LATENCY */

  /* Bus clock prescaler configuration */
  rcc->cfgr &= ~(0xful << 4); /* Set HPRE (AHB Prescaler) to 0b0xxx(1: not divided) */
  rcc->cfgr &= ~(7ul << 10); /* Clear PPRE1 */
  rcc->cfgr |= (5ul << 10);  /* Set PPRE1 (APB1 Prescaler) to 4 */
  rcc->cfgr &= ~(7ul << 13); /* Clear PPRE2 */
  rcc->cfgr |= (4ul << 13);  /* Set PPRE2 (APB2 Prescaler) to 2 */

  /* PLL configuration */
  rcc->pllcfgr |= (1ul << 22); /* Set PLLSRC bit as 0b1(HSE) */
  rcc->pllcfgr &= ~(63ul); /* Clear PLLM(6bits) */
  rcc->pllcfgr |= 4; /* Set PLLM(6bits) */
  rcc->pllcfgr &= ~(511ul << 6); /* Clear PLLN(9bits) */
  rcc->pllcfgr |= (100ul << 6);    /* Set PLLN(9bits) */
  rcc->pllcfgr &= ~(3ul << 16); /* Clear PLLP(2bits) */

  rcc->cr |= (1ul << 24); /* Set PLLON */
  while (!(rcc->cr & (1ul << 25))); /* Wait for PLLRDY bit to be set */

  /* SYSCLK selection */
  rcc->cfgr &= ~(3ul);
  rcc->cfgr |= 2ul; /* Set SW(2bits) as 0b10(PLL) */
  while (((rcc->cfgr & (3ul << 2)) >> 2) != 2); /* Wait for SWS bit to be set as PLL */
}
