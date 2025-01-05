/**
 * @file uart.h
 * @brief UART interface for STM32F446xx.
 *
 * This header file provides function declarations for initializing
 * the UART peripheral in transmit mode and implementing a custom
 * `putchar` functionality.
 *
 * @date Nov 16, 2024
 * @author klabu
 */

#ifndef __UART_H_
#define __UART_H_

#include "stm32f446xx.h"

/**
 * @brief Transmits a single character via UART.
 *
 * This function is a low-level implementation for sending a character
 * through the UART peripheral. It can be used by higher-level I/O functions.
 *
 * @param character The character to transmit.
 * @return The transmitted character.
 */
int __io_putchar(int character);

/**
 * @brief Initializes the UART peripheral for transmit mode.
 *
 * Configures the UART peripheral on the STM32F446xx microcontroller
 * for transmitting data. This setup involves enabling the UART clock,
 * configuring the GPIO pins for UART functionality, and setting up
 * basic UART parameters like baud rate.
 */
void uart_tx_init(void);

#endif /* __UART_H_ */
