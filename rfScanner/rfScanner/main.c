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


ISR(TIMER1_COMPA_vect)
{
  OCR1A = (ICR1* duty_cycle)/100;
  OCR1B = (ICR1* duty_cycle2)/100;
}

ISR(TIMER3_COMPA_vect) {
	timer_count++;  // Delay counter increment.
}

int main(void) {
	
	adc_init();
	timer_init();
	init_timer3(); //stops interrupts before setting timer3, enables interrupts after that.
	delay_ms(1);
	
    while(1)
    {
		
	float voltage= get_input_voltage(0);
	float voltage2= get_input_voltage(1);
	
	if(voltage>2.45)
    {
      if(duty_cycle<100)duty_cycle+=1;
    }
    if(voltage<1.8)
    {
      if(duty_cycle>0)duty_cycle-=1;
    }
    if(voltage2>3.3)
    {
      if(duty_cycle2<100)duty_cycle2-=1;
    }
    if(voltage2<2.8)
    {
      if(duty_cycle2>0)duty_cycle2+=1;
    }
        //TODO:: Please write your application code
    }
	return 0;
}