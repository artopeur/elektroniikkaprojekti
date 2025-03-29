/*
 * main.c
 *
 * Created: 3/22/2025 12:58:42 PM
 *  Author: artop
 */ 

//Defines
#define F_CPU 1000000UL // 1 MHz

//includes

// Introduce h files
#include "rf_adc.h"
#include "rf_delay_t3.h"

//Introduce functions


//Global variables


ISR(TIMER1_COMPA_vect) {
	timer_count++;		// left for pwm1, will need timer2 for pwm2
}

ISR(TIMER3_COMPA_vect) {
	timer_count++;  // Delay counter increment.
}

int main(void) {
	
	adc_init();
	timer_init();
	delay_ms(25);
	init_timer3(); //stops interrupts before setting timer3, enables interrupts after that.
	
	
    while(1)
    {
		float val = get_input_voltage();
		if (val == 10){
			delay_ms(10);
		}
		
        //TODO:: Please write your application code
    }
	return 0;
}