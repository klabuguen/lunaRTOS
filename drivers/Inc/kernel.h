/**
 * @file kernel.h
 * @brief Header file for the kernel implementation in an embedded RTOS.
 *
 * This file contains function declarations, constants, and macros for
 * initializing and launching the kernel, managing threads, and setting
 * timing parameters.
 */

#ifndef __KERNEL_H_
#define __KERNEL_H_

#include <stdint.h>
#include "stm32f446xx.h"

/**
 * @brief Initializes the LunaRTOS kernel.
 *
 * Sets up necessary resources such as thread control blocks (TCBs),
 * stack memory, and system tick configuration.
 */
void KernelInit(void);

/**
 * @brief Launches the LunaRTOS kernel.
 *
 * Starts the kernel's scheduler and begins execution of the created threads.
 * This function does not return as the kernel takes over the program flow.
 */
void KernelLaunch(void);

/**
 * @brief Initializes the stack for a specific thread.
 *
 * @param i The ID of the thread whose stack is being initialized.
 *
 * Sets up the stack memory for the thread, ensuring the stack pointer
 * points to the correct location and contains initial values.
 *
 * @note This function is static and intended for internal use.
 */
static void KernelStackInit(uint8_t i);

/**
 * @brief Creates threads and assigns tasks to them.
 *
 * @param task0 Pointer to the function representing the first thread's task.
 * @param task1 Pointer to the function representing the second thread's task.
 * @param task2 Pointer to the function representing the third thread's task.
 *
 * @return 0 if thread creation is successful, non-zero otherwise.
 *
 * Sets up thread control blocks (TCBs) for each task and prepares them
 * for scheduling.
 */
uint8_t KernelCreateThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void));

/**
 * @brief The time slice allocated to each thread in system ticks.
 *
 * The kernel uses this value to determine the duration for which each
 * thread runs before the scheduler switches to the next thread.
 */
const uint32_t QUANTA = 10;

/**
 * @brief Prescaler value for millisecond timing.
 *
 * This value is derived from the system clock frequency and is used to
 * convert system ticks into milliseconds for time calculations.
 */
uint32_t MS_PRESCALER;

#endif // __KERNEL_H_
