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

//Introduce functions
void pause_ms(uint16_t);

//Global variables
volatile uint16_t timer_count = 0;

ISR(TIMER1_COMPA_vect) {
	timer_count++;
}

int main(void) {
	
	adc_init();
	timer_init();
	pause_ms(25);
	
    while(1)
    {
		float val = get_input_voltage();
		if (val == 10){
			pause_ms(10);
		}
		
        //TODO:: Please write your application code
    }
	return 0;
}

void pause_ms(uint16_t ms) {
	// Double check with ms counting.
	timer_count = 0;
	while (timer_count < ms);
}
