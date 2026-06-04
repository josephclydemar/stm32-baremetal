#include "stm32f411xx.h"
#include "usart.h"

void usart_init(usart_dev_t usart_dev, usart_brr_t brr_cfg)
{
  usart_dev.usart->cr[0] &= ~USART_CR1_M; // Clear M bit (8 data bits) 
  usart_dev.usart->cr[0] &= ~USART_CR1_OVER8; // Clear OVER8 bit

  usart_dev.usart->brr &= ~(0xffff);
  usart_dev.usart->brr |= (brr_cfg.mantissa << 4);
  usart_dev.usart->brr |= brr_cfg.fraction;

  nvic_enable_irq((nvic_t *)NVIC_START, usart_dev.irq_pos, usart_dev.irq_priority);
  usart_dev.usart->cr[0] |= (USART_CR1_TE | USART_CR1_RE); // Enable TX and RX
  usart_dev.usart->cr[0] |= USART_CR1_RXNEIE; // Enable RXNE Interrupt
  usart_dev.usart->cr[0] |= USART_CR1_UE; // Set UE (Enable USART)
}

void usart_send(usart_dev_t usart_dev, const uint8_t *buff, const uint32_t buff_len)
{
  for (uint32_t i = 0; i < buff_len; ++i) {
    while (!(usart_dev.usart->sr & USART_SR_TXE));
    usart_dev.usart->dr = buff[i];
  }
  while (!(usart_dev.usart->sr & USART_SR_TC));
}
