#include "kernel.h" 

// Define the number of threads in the system
#define NUM_THREADS         3  
// Define the maximum stack size for each thread
#define MAX_STACK_SIZE      100  

// Thread Control Block (TCB) structure definition
typedef struct {
    int32_t *stackPtr;        // Pointer to the top of the stack for this thread
    tcb_t *nextStackPtr;      // Pointer to the next TCB in the linked list (for round-robin scheduling)
} tcb_t;

// Array of TCBs, one for each thread
tcb_t tcb[NUM_THREADS]; 

// Pointer to the currently executing thread's TCB
tcb_t *currStackPtr;

// Array representing the stacks for each thread
// Each thread is assigned its own stack space
int32_t TCB_STACK[NUM_THREADS][MAX_STACK_SIZE];
