/*
 * main.c
 *
 * Created: 3/22/2025 12:58:42 PM
 *  Author: artop, tuomast, attek
 */ 

//Defines
#define F_CPU 1000000UL // 1 MHz

//includes

// Introduce h files
#include "rf_adc.h"
#include "rf_delay_t3.h"
#include "rf_disp.h"
#include "rf_meas.h"
#include "rf_I2C.h"

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
	
	
	uint8_t rf_meas_counter = 0;
	
	adc_init();
	timer_init();
	init_timer3(); //stops interrupts before setting timer3, enables interrupts after that.
	delay_ms(1);
	initI2C();
	
    while(1)
    {
		
		float voltage= get_input_voltage(0);
		float voltage2= get_input_voltage(1);
		uint16_t rfvalue = adc_read(2);
	
		if(voltage>2.1)
		{
		  if(duty_cycle<100)duty_cycle+=1;
		}
		if(voltage<2.1)
		{
		  if(duty_cycle>0)duty_cycle-=1;
		}
		if(voltage2>3.2)
		{
		  if(duty_cycle2<100)duty_cycle2-=1;
		}
		if(voltage2<3.2)
		{
		  if(duty_cycle2>0)duty_cycle2+=1;
		}
		
		float rfvolts = measurement(rfvalue, voltage); // tests previous value to previous measurement and if it is larger, returns that, otherwise returns previous highest value.
		if(rfvolts == rfvalue) {
			// no need to update display
			rf_meas_counter++;
		}
		else {
			// print rfvolts to display.
			rf_meas_counter++;
		}		
		if(rf_meas_counter > 200) {
			rf_meas_counter = 0;
			reset_measurement();	// if value of meas_counter is over 200, resets the highest previous value to 0.00
		}
		
    }
	
	return 0;
}