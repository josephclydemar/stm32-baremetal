#include "rcc.h"

void rcc_periph_enable(rcc_periph_t p)
{
  *p.reg |= p.mask;
}

void rcc_pll_config(void)
{
  rcc_t *rcc = (rcc_t *)RCC_ADDR;
  pwr_t *pwr = (pwr_t *)PWR_ADDR;
  flash_intf_t *flash = (flash_intf_t *)FLASH_INTF_ADDR;

  rcc->cr |= RCC_CR_HSEON; /* Set HSEON bit */  
  while (!(rcc->cr & RCC_CR_HSERDY)); /* Wait for HSERDY bit to be set */

  /* Voltage scaling configuration */
  rcc->apbenr[0] |= RCC_APB1ENR_PWREN; /* Set PWREN bit */
  pwr->cr |= (3ul << 14); /* Set VOS bit (Scale 1) */

  /* Flash configuration for caching, prefetching, wait state */
  flash->acr |= (7ul << 8); /* Set the bits ICEN, DCEN, PRFTEN */
  flash->acr &= ~(0xful); /* Clear LATENCY */
  flash->acr |= 5ul;      /* Set LATENCY */

  /* Bus clock prescaler configuration */
  rcc->cfgr &= ~RCC_CFGR_HPRE_DIV512; /* Set HPRE (AHB Prescaler) to 0b0xxx(1: not divided) */
  rcc->cfgr &= ~RCC_CFGR_PPRE1_DIV16; /* Clear PPRE1 */
  rcc->cfgr |= RCC_CFGR_PPRE1_DIV4;  /* Set PPRE1 (APB1 Prescaler) to 4 */
  rcc->cfgr &= ~RCC_CFGR_PPRE2_DIV16; /* Clear PPRE2 */
  rcc->cfgr |= RCC_CFGR_PPRE2_DIV2;  /* Set PPRE2 (APB2 Prescaler) to 2 */

  /* PLL configuration */
  rcc->pllcfgr |= RCC_PLLCFGR_PLLSRC; /* Set PLLSRC bit as 0b1(HSE) */
  rcc->pllcfgr &= ~(63ul); /* Clear PLLM(6bits) */
  rcc->pllcfgr |= 4; /* Set PLLM(6bits) */
  rcc->pllcfgr &= ~(511ul << 6); /* Clear PLLN(9bits) */
  rcc->pllcfgr |= (100ul << 6);    /* Set PLLN(9bits) */
  rcc->pllcfgr &= ~RCC_PLLCFGR_PLLP_DIV8; /* Clear PLLP(2bits) */

  rcc->cr |= RCC_CR_PLLON; /* Set PLLON */
  while (!(rcc->cr & RCC_CR_PLLRDY)); /* Wait for PLLRDY bit to be set */

  /* SYSCLK selection */
  rcc->cfgr &= ~RCC_CFGR_SW_NOTALLOWED;
  rcc->cfgr |= RCC_CFGR_SW_PLL; /* Set SW(2bits) as 0b10(PLL) */
  while (((rcc->cfgr & RCC_CFGR_SWS_NOTAPPLICABLE) >> 2) != 2); /* Wait for SWS bit to be set as PLL */
}
