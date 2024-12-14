#include "kernel.h" 

// Define system clock
#define SYS_CLOCK 			16000000
// Define the number of threads in the system
#define NUM_THREADS         3  
// Define the maximum stack size for each thread
#define MAX_STACK_SIZE      100


// Thread Control Block (TCB) structure definition
typedef struct tcb_t{
    int32_t *stackPtr;        // Pointer to the top of the stack for this thread
    struct tcb_t *nextStackPtr;      // Pointer to the next TCB in the linked list (for round-robin scheduling)
} tcb_t;

// Array of TCBs, one for each thread
tcb_t tcb[NUM_THREADS]; 

// Pointer to the currently executing thread's TCB
tcb_t *currStackPtr;

// Array representing the stacks for each thread
// Each thread is assigned its own stack space
int32_t TCB_STACK[NUM_THREADS][MAX_STACK_SIZE];

// Prescaler value for millisecond timing
uint32_t MS_PRESCALER;

static void KernelStackInit(uint8_t i);
static void SchedulerLaunch(void);

void KernelInit(void){
	MS_PRESCALER = SYS_CLOCK / 1000;
}

void KernelLaunch(uint32_t quanta){
	// Reset SysTick timer
	SysTick->CTRL = 0;

    // Clear the SysTick Current Value Register to start counting from zero
    SysTick->VAL = 0;

    // Configure SysTick Reload Value Register to equal the quanta value
    SysTick->LOAD = (quanta * MS_PRESCALER) - 1;

    // Set SysTick to lowest priority
    // Necessary to prioritize hardware interrupts
    NVIC_SetPriority(SysTick_IRQn, 15);

    // Select the processor clock as the SysTick clock source
    SysTick->CTRL |= (1U << 2);

    // Enable the SysTick counter
    SysTick->CTRL |= (1U << 0);

    // Enable SysTick interrupt request
    SysTick->CTRL |= (1U << 1);

    // Launch the Scheduler
    SchedulerLaunch();

}

uint8_t KernelCreateThreads(void(*task0)(void), void(*task1)(void), void(*task2)(void)){
	// Disable global interrupts
	__disable_irq();

	// Initialize TCB *nextStackPtr for each thread
	tcb[0].nextStackPtr = &tcb[1];
	tcb[1].nextStackPtr = &tcb[2];
	tcb[2].nextStackPtr = &tcb[0];

	// Initialize stack for thread 0
	KernelStackInit(0);
	// Initialize PC for thread 0
	TCB_STACK[0][MAX_STACK_SIZE-2] = (int32_t)(task0);

	// Initialize stack for thread 1
	KernelStackInit(1);
	// Initialize PC for thread 1
	TCB_STACK[1][MAX_STACK_SIZE-2] = (int32_t)(task1);

	// Initialize stack for thread 2
	KernelStackInit(2);
	// Initialize PC for thread 0
	TCB_STACK[2][MAX_STACK_SIZE-2] = (int32_t)(task2);

	// Start from thread 0
	currStackPtr = &tcb[0];

	// Enable global interrupts
	__enable_irq();

	return 1;
}

static void KernelStackInit(uint8_t i){
	// Initialize Stack Pointer (R13)
	tcb[i].stackPtr = &TCB_STACK[i][MAX_STACK_SIZE-16];
	// Set thumb bit 24 in the EPSR to 1
	// The Cortex-M4 processor only supports execution of instructions in Thumb state
	TCB_STACK[i][MAX_STACK_SIZE-1] = (1U <<  24);

	// Initialize the stack content to 0xAAAAAAAA
	// Link Register (R14)
	TCB_STACK[i][MAX_STACK_SIZE-3] = 0xAAAAAAAA;
	// R12
	TCB_STACK[i][MAX_STACK_SIZE-4] = 0xAAAAAAAA;
	// R3
	TCB_STACK[i][MAX_STACK_SIZE-5] = 0xAAAAAAAA;
	// R2
	TCB_STACK[i][MAX_STACK_SIZE-6] = 0xAAAAAAAA;
	// R1
	TCB_STACK[i][MAX_STACK_SIZE-7] = 0xAAAAAAAA;
	// R0
	TCB_STACK[i][MAX_STACK_SIZE-8] = 0xAAAAAAAA;

	// Initialize additional general-purpose registers
	// R11
	TCB_STACK[i][MAX_STACK_SIZE-9] = 0xAAAAAAAA;
	// R10
	TCB_STACK[i][MAX_STACK_SIZE-10] = 0xAAAAAAAA;
	// R9
	TCB_STACK[i][MAX_STACK_SIZE-11] = 0xAAAAAAAA;
	// R8
	TCB_STACK[i][MAX_STACK_SIZE-12] = 0xAAAAAAAA;
	// R7
	TCB_STACK[i][MAX_STACK_SIZE-13] = 0xAAAAAAAA;
	// R6
	TCB_STACK[i][MAX_STACK_SIZE-14] = 0xAAAAAAAA;
	// R5
	TCB_STACK[i][MAX_STACK_SIZE-15] = 0xAAAAAAAA;
	// R4
	TCB_STACK[i][MAX_STACK_SIZE-16] = 0xAAAAAAAA;
}

__attribute__((naked)) void SysTick_Handler(void) {
	// Disable global interrupts
	__asm("CPSID	I");

	// Suspend the current thread
	// Save remaining general-purpose registers (R4, R5, R6, R7, R9, R10, R11)
	__asm("PUSH {R4-R11}");
	// Load address of currStackPtr into R0
	__asm("LDR R0,=currStackPtr");
	// Load R1 from address R0 (R1= currStackPtr)
	__asm("LDR R1,[R0]");
	// Store ARM Cortex-M SP from address R1
	__asm("STR SP,[R1]");

	// Choose the next thread
	// Load ARM Cortex-M SP from address 4 bytes above R1
	__asm("LDR R1,[R1,#4]");
	// Store R1 in at address R0
	__asm("STR R1,[R0]");
	// Load ARM Cortex-M SP from address R1
	__asm("LDR SP,[R1]");
	// Restore R4-R11
	__asm("POP {R4-R11}");

	// Enable global interrupts
	__asm("CPSIE	I");

	// Return from exception
	// Restore R0, R1, R2, R3, R12, LR, PC, PSR
	__asm("BX	LR");
}

static void SchedulerLaunch(void){
	// Load currentPtr address into R0
	__asm("LDR R0,=currStackPtr");
	// Load R2 from address R0 (Set R2=currStackPtr)
	__asm("LDR R2,[R0]");
	// Load ARM Cortex-M SP from address R2
	__asm("LDR SP,[R2]");
	// Restore R4-R11
	__asm("POP {R4-R11}");
	// Restore R12
	__asm("POP {R12}");
	// Restore R0, R1, R2, R3
	__asm("POP {R0-R3}");
	// Skip LR
	__asm("ADD SP,SP,#4");
	// Pop LR to create new start location
	__asm("POP {LR}");
	// Skip PSR
	__asm("ADD SP,SP,#4");
	// Enable global interrupts
	__asm("CPSIE	I");
	// Return from exception
	__asm("BX	LR");
}
