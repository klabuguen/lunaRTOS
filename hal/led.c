#include "led.h"

void led_init(void){
    // Enable clock for GPIOA by setting the AHB1ENR register bit for GPIOA (bit 0)
    RCC->AHB1ENR |= (1U << 0);

    // Configure PA5 as output:
    // Set bit 10 to 1 (MODER5[1:0] = 0b01 for general-purpose output mode)
    GPIOA->MODER |= (1U << 10);

    // Ensure bit 11 is cleared to 0 (MODER5[1] = 0)
    GPIOA->MODER &= ~(1U << 11);
}

void led_on(void){
    // Set PA5 (bit 5 of BSRR) to high, turning on the LED.
    GPIOA->BSRR |= (1U << 5);
}

void led_off(void){
    // Reset PA5 (bit 21 of BSRR) to low, turning off the LED.
    // The high part of BSRR (bits 16-31) is used to reset pins.
    GPIOA->BSRR |= (1U << 21);
}
