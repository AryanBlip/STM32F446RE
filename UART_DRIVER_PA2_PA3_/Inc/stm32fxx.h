#ifndef STM32F446XX_H
#define STM32F446XX_H

#include <stdint.h>

// Base addresses for peripherals
#define RCC_BASE    0x40023800UL
#define GPIOA_BASE  0x40020000UL
#define USART2_BASE 0x40004400UL

// ENABLE BUS
#define RCC_AHB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR  (*(volatile uint32_t *)(RCC_BASE + 0x40))

// SET MODE TO ALTERNATE FUNCTION
#define GPIOA_MODER  (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFR0   (*(volatile uint32_t *)(GPIOA_BASE + 0x20)) // AFR[0] is at offset 0x20

// DEFINE USART2 PERIPHERALS
#define USART2_SR   (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR   (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR  (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1  (*(volatile uint32_t *)(USART2_BASE + 0x0C))
#define USART2_CR2  (*(volatile uint32_t *)(USART2_BASE + 0x10))
#define USART2_CR3  (*(volatile uint32_t *)(USART2_BASE + 0x14))

// BUS CLOCK definitions
#define RCC_AHB1ENR_GPIOAEN   (1u << 0)
#define RCC_APB1ENR_USART2EN  (1u << 17)

// DEFINE USART2_CR1_BIT_FIELDS
#define USART2_CR1_RE     (1UL << 2)
#define USART2_CR1_TE     (1UL << 3)
#define USART2_CR1_M      (1UL << 12)
#define USART2_CR1_UE     (1UL << 13)
#define USART2_CR1_OVER8  (1UL << 15)

// DEFINE USART2_CR2_BIT FIELDS
#define USART2_CR2_LBDIE  (1UL << 6)
#define USART2_CR2_CLKEN  (1UL << 11)
#define USART2_CR2_STOP   (3UL << 12)
#define USART2_CR2_LINEN  (1UL << 14)

// DEFINE USART2_CR3_BIT_FIELDS
#define USART2_CR3_EIE     (0x01UL)
#define USART2_CR3_IREN    (0x01UL << 1)
#define USART2_CR3_ONEBIT  (0x01 << 11)

// Status register masks
#define USART_SR_RXNE  (1u << 5)
#define USART_SR_TXE   (1u << 7)

// LD2 OUTPUT REGISTER
#define LD2 (*(volatile uint32_t*) 0x40020014)

#endif /* STM32F446XX_H */
