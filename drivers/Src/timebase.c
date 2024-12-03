/*
 * timebase.c
 *
 *  Created on: Nov 16, 2024
 *      Author: klabu
 */

#include <stdint.h>
#include "timebase.h"

#define MAX_DELAY	0xFFFFFFFF ///< Maximum value for delay calculation

// Global variables for tracking the system tick count
volatile uint32_t g_current_tick = 0;       ///< Current tick count
volatile uint32_t g_current_tick_p = 0;  ///< Snapshot of tick count for atomic access
volatile uint32_t tick_frequency = 1;      ///< Tick frequency (ticks per second)

void increment_tick(void) {
	// Increment tick count by the tick frequency
	g_current_tick += tick_frequency;
}

uint32_t get_tick(void) {
	// Temporarily disable interrupts for atomic access
	__disable_irq();

	// Take a snapshot of the tick count
	g_current_tick_p = g_current_tick;

	// Re-enable interrupts
	__enable_irq();

	// Return the snapshot
	return g_current_tick_p;
}

void delay(uint32_t seconds) {
	// Record the tick count at the start of the delay
	uint32_t tick_start = get_tick();

	// Calculate the delay duration in ticks
	uint32_t wait = seconds;

	// Prevent overflow by capping the wait time
	if (wait < MAX_DELAY) {
		// Add one tick to ensure the full duration is covered
		wait += tick_frequency;
	}

	// Block until the required duration has passed
	while ((get_tick() - tick_start) < wait) {}
}

void timebase_init(void) {
    // Configure SysTick Reload Value Register for a 1-second interval
    SysTick->LOAD = 16000000 - 1;

    // Clear the SysTick Current Value Register to start counting from zero
    SysTick->VAL = 0;

    // Select the processor clock as the SysTick clock source
    SysTick->CTRL |= (1U << 2);

    // Enable SysTick interrupt request
    SysTick->CTRL |= (1U << 1);

    // Enable the SysTick counter
    SysTick->CTRL |= (1U << 0);

    // Enable global interrupts to allow SysTick interrupts
    __enable_irq();
}

void SysTick_Handler(void) {
	// Increment the tick count on each SysTick interrupt
	increment_tick();
}
