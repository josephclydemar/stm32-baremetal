/* STM32F411xx */
#include <stdint.h>

extern uint32_t _estack, _sidata, _sdata, _edata, _sbss, _ebss;

int main(void);
void default_handler(void);
void reset_handler(void);
void nmi_handler(void);
void hardfault_handler(void);
void memmanage_handler(void);
void busfault_handler(void);
void usagefault_handler(void);
void svc_handler(void);
void debugmon_handler(void);
void pendsv_handler(void);
void stk_handler(void);
void usart2_handler(void);
void usart6_handler(void);

/* vector table */
__attribute__((section(".isr_vector")))
void (*const vector_table[])(void) = {
  (void (*)(void))(&_estack),  // 0: Initial stack pointer
  reset_handler,               // 1: Reset
  nmi_handler,                 // 2
  hardfault_handler,           // 3
  memmanage_handler,           // 4
  busfault_handler,            // 5
  usagefault_handler,          // 6
  0, 0, 0, 0,                 // 7–10 reserved
  svc_handler,                 // 11
  debugmon_handler,            // 12
  0,                           // 13 reserved
  pendsv_handler,              // 14
  stk_handler,             // 15

  /* ---- STM32F411 IRQ ---- */
  default_handler, //   (0): WWDG
  default_handler, //   (1): PVD
  default_handler, //   (2): TAMP_STAMP
  default_handler, //   (3): RTC_WKUP
  default_handler, //   (4): FLASH
  default_handler, //   (5): RCC
  default_handler, //   (6): EXTI0
  default_handler, //   (7): EXTI1
  default_handler, //   (8): EXTI2
  default_handler, //   (9): EXTI3
  default_handler, //  (10): EXTI4
  default_handler, //  (11): DMA1_Stream0
  default_handler, //  (12): DMA1_Stream1
  default_handler, //  (13): DMA1_Stream2
  default_handler, //  (14): DMA1_Stream3
  default_handler, //  (15): DMA1_Stream4
  default_handler, //  (16): DMA1_Stream5
  default_handler, //  (17): DMA1_Stream6
  default_handler, //  (18): ADC
  0, //  (19):
  0, //  (20):
  0, //  (21):
  0, //  (22):
  default_handler, //  (23): EXTI9_5
  default_handler, //  (24): TIM1_BRK_TIM9
  default_handler, //  (25): TIM1_UP_TIM10
  default_handler, //  (26): TIM1_TRG_COM_TIM11
  default_handler, //  (27): TIM1_CC
  default_handler, //  (28): TIM2
  default_handler, //  (29): TIM3
  default_handler, //  (30): TIM4
  default_handler, //  (31): I2C1_EV
  default_handler, //  (32): I2C1_ER
  default_handler, //  (33): I2C2_EV
  default_handler, //  (34): I2C2_ER
  default_handler, //  (35): SPI1
  default_handler, //  (36): SPI2
  default_handler, //  (37): USART1
  usart2_handler,  //  (38): USART2
  default_handler, //  (39): 
  default_handler, //  (40): 
  default_handler, //  (41): 
  default_handler, //  (42): 
  default_handler, //  (43): 
  default_handler, //  (44): 
  default_handler, //  (45): 
  default_handler, //  (46): 
  default_handler, //  (47): 
  default_handler, //  (48): 
  default_handler, //  (49): 
  default_handler, //  (50): 
  default_handler, //  (51): 
  default_handler, //  (52): 
  default_handler, //  (53): 
  default_handler, //  (54): 
  default_handler, //  (55): 
  default_handler, //  (56): 
  default_handler, //  (57): 
  default_handler, //  (58): 
  default_handler, //  (59): 
  default_handler, //  (60): 
  default_handler, //  (61): 
  default_handler, //  (62): 
  default_handler, //  (63): 
  default_handler, //  (64): 
  default_handler, //  (65): 
  default_handler, //  (66): 
  default_handler, //  (67): 
  default_handler, //  (68): 
  default_handler, //  (69): 
  default_handler, //  (70): 
  usart6_handler, //  (71): USART6
  default_handler, //  (72): 
  default_handler, //  (73): 
};

