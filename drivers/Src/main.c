#include <stdio.h>
#include <stdint.h>
#include "led.h"
#include "uart.h"
#include "timebase.h"

int main(void){
	timebase_init();
	led_init();
	uart_tx_init();
	while(1){
		 led_on();
		 printf("led on\n\r");
		 delay(1);
		 led_off();
		 printf("led off\n\r");
		 delay(1);
	}

}
