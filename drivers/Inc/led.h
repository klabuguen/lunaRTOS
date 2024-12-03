/**
 * @file led.h
 * @brief LED control interface for STM32F446xx.
 *
 * This header file provides function declarations for initializing
 * and controlling an LED on the STM32F446xx microcontroller.
 *
 * @date Nov 16, 2024
 * @author klabu
 */

#ifndef __LED_H_
#define __LED_H_

#include "stm32f446xx.h"

/**
 * @brief Initializes the LED GPIO.
 *
 * Configures the GPIO pin connected to the LED as an output.
 * This function must be called before using any other LED functions.
 */
void led_init(void);

/**
 * @brief Turns the LED on.
 *
 * Sets the GPIO pin connected to the LED to a high state,
 * turning the LED on.
 */
void led_on(void);

/**
 * @brief Turns the LED off.
 *
 * Sets the GPIO pin connected to the LED to a low state,
 * turning the LED off.
 */
void led_off(void);

#endif /* __LED_H_ */
