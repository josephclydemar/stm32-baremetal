#include "usart.h"

void usart_init(usart_t *usart, usart_brr_t brr_cfg)
{
  usart->cr[0] &= ~USART_CR1_M; // Clear M bit (8 data bits) 
  usart->cr[0] &= ~USART_CR1_OVER8; // Clear OVER8 bit

  usart->brr &= ~(0xffff);
  usart->brr |= (brr_cfg.mantissa << 4);
  usart->brr |= brr_cfg.fraction;

  usart->cr[0] |= (USART_CR1_TE | USART_CR1_RE); // Enable TX and RX
  usart->cr[0] |= USART_CR1_UE; // Set UE (Enable USART)
}

void usart_send(usart_t *usart, char *buff, uint32_t buff_len)
{
  for (uint32_t i = 0; i < buff_len; ++i) {
    while (!(usart->sr & USART_SR_TXE));
    usart->dr = buff[i];
  }
}

void usart_recv(usart_t *usart, char *buff, usart_t buff_len)
{
  (void)usart;
  (void)buff;
  (void)buff_len;
}
