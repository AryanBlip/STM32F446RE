#include <stdint.h>

// Base addresses for peripherals
#define RCC_BASE      0x40023800UL
#define GPIOA_BASE    0x40020000UL
#define USART1_BASE   0x40011000UL

// Direct Register Definitions (Base Address + Offset)
#define RCC_AHB1ENR   (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB2ENR   (*(volatile uint32_t *)(RCC_BASE + 0x44))

#define GPIOA_MODER   (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFR1    (*(volatile uint32_t *)(GPIOA_BASE + 0x24)) // AFR[1] is the alternate function high register

#define USART1_ISR     (*(volatile uint32_t *)(USART1_BASE + 0x00)) /* Status register,        Address offset: 0x00 */
#define USART1_DR     (*(volatile uint32_t *)(USART1_BASE + 0x04)) /* Data register (RDR/TDR), Address offset: 0x04 */
#define USART1_BRR    (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1    (*(volatile uint32_t *)(USART1_BASE + 0x0C))
#define USART1_CR2    (*(volatile uint32_t *)(USART1_BASE + 0x10))
#define USART1_CR3    (*(volatile uint32_t *)(USART1_BASE + 0x14))

// BUS CLOCK definitions
#define RCC_AHB1ENR_GPIOAEN   (1u << 0) //0x01
#define RCC_APB2ENR_USART1EN  (1u << 4) //0x10


// DEFINE USART1_CR1_BIT_FIELDS
#define USART1_CR1_RE          (1UL << 2)   /* Receiver enable */
#define USART1_CR1_TE          (1UL << 3)   /* Transmitter enable */
#define USART1_CR1_M           (1UL << 12)  /* Word length selection */
#define USART1_CR1_UE          (1UL << 13)  /* USART enable */
#define USART1_CR1_OVER8       (1UL << 15)  /* Oversampling mode */


// DEFINE USART_CR2_BIT FIELDS
#define USART1_CR2_LBDIE      (1UL << 6)   // Bit 6
#define USART1_CR2_CLKEN      (1UL << 11)  // Bit 11
#define USART1_CR2_STOP       (3UL << 12)  // Bits 13:12 (Clearing both forces 00 -> 1 Stop Bit)
#define USART1_CR2_LINEN      (1UL << 14)  // Bit 14

// DEFINE USART_CR3_BIT_FIELDS
#define USART1_CR3_EIE		(0x01UL)   // BIT 0
#define USART1_CR3_IREN		(0x01UL << 1)   // BIT 1
#define USART1_CR3_ONEBIT	(0x01 << 11) // BIT 11


#define USART_ISR_TXE 		(1UL << 7)
#define USART_ISR_RXNE 		(1UL << 5)
