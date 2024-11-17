/*
 * uart.c
 *
 *  Created on: Nov 16, 2024
 *      Author: klabu
 */

#include "uart.h"

#define SYS_CLOCK 16000000
#define APB1_CLOCK SYS_CLOCK
#define UART_BAUDRATE 115200

void uart_tx_init(void){
    // Enable clock for GPIOA by setting the AHB1ENR register bit for GPIOA (bit 0)
    RCC->AHB1ENR |= (1U << 0);

    // Configure PA2 to be in alternate function mode:
    // Ensure bit 4 is set to 0 (MODER5[1:0] = 0b10 for alternate function mode)
    GPIOA->MODER &= ~(1U << 4);
    // Set bit 5 to 1 (MODER5[1:0] = 0b10 for alternate function mode)
    GPIOA->MODER |= (1U << 5);

    // Set alternate function type to AF07
    // Ensure bit 8, bit 9, bit 10 are set to 1 (AFRL2[3:0] = 0b0111)
    GPIOA->AFR[0] |= (1U << 8);
    GPIOA->AFR[0] |= (1U << 9);
    GPIOA->AFR[0] |= (1U << 10);
    // Set bit 11 to 0
    GPIOA->AFR[0] &= !(1U << 11);

    // Enable clock for USART2 by setting the AHB1ENR register bit for USART2 (bit 17)
    RCC->APB1ENR |= (1U << 17);

    // Configure baud rate
    USART2->BRR = (uint16_t) (APB1_CLOCK + (UART_BAUDRATE / 2U) / UART_BAUDRATE);

    // Configure transfer direction by setting the USART_CR1 transmit enable (TE) register bit to 1 (bit 3)
    USART2->CR1 = (1U << 3);

    // Enable UART module by setting the USART_CR2 USART enable (UE) register bit to 1 (bit 13)
    USART2->CR1 |= (1U << 13);

}
