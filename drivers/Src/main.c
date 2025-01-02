#include <stdio.h>
#include "led.h"
#include "uart.h"
#include "kernel.h"

#define QUANTA	10

typedef uint32_t TaskProfiler;


TaskProfiler Task0_Profiler = 0, Task1_Profiler = 0,Task2_Profiler = 0;
TaskProfiler pTask1_Profiler = 0, pTask2_Profiler = 0;
int32_t semaphore1,semaphore2;

void motor_run(void);
void motor_stop(void);
void valve_open(void);
void valve_close(void);


void task0(void)
{  
	while(1)
	{
		Task0_Profiler++;
		ThreadYield();
	}
}


void task1(void)
{
	while(1)
	{
		SemaphoreWait(&semaphore1);
		motor_run();
//		Task1_Profiler++;
//		ThreadYield();
//		valve_open();
		SemaphoreGive(&semaphore2);
	}
}

void task2(void)
{
	while(1)
	{
		SemaphoreWait(&semaphore2);
		valve_open();
//		Task2_Profiler++;
//		ThreadYield();
//		motor_stop();
		SemaphoreGive(&semaphore1);
	}
}

void task3(void){
	pTask1_Profiler++;
}

int main(void)
{
	// Initialize UART
	uart_tx_init();
	// Initialize TIM2
	TIM2_1Hz_Interrupt_Init();
	// Initialize Semaphore1 & Semaphore2
	SemaphoreInit(&semaphore1, 1);
	SemaphoreInit(&semaphore2, 0);
	/*Initialize Kernel*/
	KernelInit();
	/*Add Threads*/
	KernelCreateThreads(&task0,&task1,&task2);

	/*Set RoundRobin time quanta*/
	KernelLaunch(QUANTA);


}

void TIM2_IRQHandler(void){
	TIM2->SR &= ~(1 << 0);
	pTask2_Profiler++;
}


void motor_run(void)
{
	printf("Motor is starting...\n\r");

}


void motor_stop(void)
{
	printf("Motor is stopping...\n\r");
}

void valve_open(void)
{
	printf("Valve is opening...\n\r");
}


void valve_close(void)
{
	printf("Valve is closing...\n\r");
}


