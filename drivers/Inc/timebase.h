/**
 * @file timebase.h
 * @brief Timebase management for STM32F446xx.
 *
 * This header file provides function declarations for timebase
 * management, including tick incrementing, retrieving the current
 * tick count, implementing delays, and initializing the timebase
 * system using the SysTick timer.
 *
 * @date Nov 16, 2024
 * @author klabu
 */

#ifndef __TIMEBASE_H_
#define __TIMEBASE_H_

#include <stdint.h>
#include "stm32f446xx.h"

/**
 * @brief Increments the system tick counter.
 *
 * This function is typically called in the SysTick interrupt handler
 * to update the tick count. It serves as the core of the timebase mechanism.
 */
void increment_tick(void);

/**
 * @brief Retrieves the current system tick count.
 *
 * This function returns the current value of the system tick counter,
 * which represents the number of ticks since the timebase was initialized.
 *
 * @return The current tick count as a 32-bit unsigned integer.
 */
uint32_t get_tick(void);

/**
 * @brief Delays the execution for a specified number of seconds.
 *
 * Uses the system tick counter to create a blocking delay.
 *
 * @param seconds The number of seconds to delay.
 */
void delay(uint32_t seconds);

/**
 * @brief Initializes the timebase system.
 *
 * Configures and starts the SysTick timer to serve as the timebase for
 * the application. This includes setting the reload value and enabling
 * the SysTick interrupt.
 */
void timebase_init(void);

/**
 * @brief SysTick interrupt handler.
 *
 * Handles the SysTick interrupt, typically by calling the
 * `increment_tick` function to update the system tick count.
 */
void SysTick_Handler(void);

#endif /* __TIMEBASE_H_ */
