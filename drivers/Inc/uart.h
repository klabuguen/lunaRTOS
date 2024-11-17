/**
 * @file uart.h
 * @brief UART interface for STM32F446xx.
 *
 * This header file provides the function declaration for UART
 * initialization in transmit mode.
 *
 * @date Nov 16, 2024
 * @author klabu
 */

#ifndef __UART_H_
#define __UART_H_

#include "stm32f446xx.h"

/**
 * @brief Initializes UART TX.
 *
 * Configures the UART peripheral for transmitting data.
 * This function sets up the baud rate and enables the UART
 * transmitter.
 */
void uart_tx_init(void);

#endif /* __UART_H_ */
