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
void KernelLaunch(uint32_t quanta);

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

#endif // __KERNEL_H_
