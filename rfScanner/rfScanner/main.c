/*
 * main.c
 *
 * Created: 3/22/2025 12:58:42 PM
 *  Author: artop, tuomast, attek
 */ 

//Defines
#define F_CPU 2000000UL // 1 MHz

//includes

// Introduce h files
#ifndef ARDUINO
	#include "rf_adc.h"
	#include "rf_delay_t3.h"
	#include "rf_disp.h"
	#include "rf_meas.h"
	#include "rf_I2C.h"
#endif
//Introduce functions

void test_delay(uint8_t ms);

//Global variables
//volatile float voltage= 0.00;
//volatile float voltage2= 0.00;
volatile uint16_t voltage = 0;
volatile uint16_t voltage2 = 0;

//*
ISR(TIMER1_COMPA_vect)
{

	//voltage= get_input_voltage(0);
	//voltage2= get_input_voltage(1);
	voltage = adc_read(0);
	voltage2 = adc_read(1);
	//*
	if(voltage>67)
	{
		if(duty_cycle<100)duty_cycle+=1;
	}
	if(voltage<67)
	{
		if(duty_cycle>0)duty_cycle-=1;
	}
	//*/
	//*
	if(voltage2>78)
	{
		if(duty_cycle2<100)duty_cycle2-=1;
	}
	if(voltage2<78)
	{
		if(duty_cycle2>0)duty_cycle2+=1;
	}
	OCR1A = (ICR1* duty_cycle)/100;
	OCR1B = (ICR1* duty_cycle2)/100;
	
}
//*/
//*
ISR(TIMER0_COMPA_vect) {
	timer_count++;  // Delay counter increment.
}
//*/

#ifndef ARDUINO
int main(void) {
#endif
#ifdef ARDUINO
int run(void) {
#endif
	#ifdef ARDUINO
		Serial.begin(19200);
		//initDisp();
		//Serial.println("test");
		//initDisp();
		Serial.println("init done.");
		delay(100);
		
	#endif
	uint16_t rf_meas_counter = 0;
	
	// From page 62 / 294, the unconnected pins to save power consumption. They are floating after reset.
	// Unused ports of port D
	DDRD = 0x00;
	PORTD = 0xFF; //set pull-up functionality.

	// PB0
	DDRB &= ~(1 << PB0);
	PORTB |= (1 << PB0);

	// ADC6, ADC7 If they are available.
	//DDRC &= ~((1 << PC6) | (1 << PC7));        // Set PC6 and PC7 as input
    //PORTC |= (1 << PC6) | (1 << PC7);          // Enable pull-ups on PC6 and PC7
	
	adc_init();
	timer_init();
	init_timer3(); //stops interrupts before setting timer3, enables interrupts after that.
	test_delay(10);

	screen.initI2C();
	screen.init();
	//initDisp();
	test_delay(100);

    while(1)
    {
		#ifdef ARDUINO
			//Serial.println("Testing");
			//test_delay(100);
			delay(1);
		#endif

		#ifdef ARDUINO
			//Serial.println(voltage);
			//test_delay(1);
		#endif
		//*
		unsigned char start[6] = "data:";
		screen.set(1,start);
		
		unsigned char measure[20] = "";
		volatile float data = 0.1;
		volatile float rfdata = 0.11;
		screen.clear();
		/*
		setText(1,buffer);
		//*/
		//*
		for (uint8_t i = 0; i<50;i++) {
			if(i < 25) {
				data = data + 0.1;
				rfdata = rfdata+0.11;
			}
			else {
				data=data - 0.1;
				rfdata=rfdata-0.11;
			}
		
			clearBuffer(strlenCustom(measure),measure);
			unsigned char result [20] = "";
			screen.floatToChar(data,measure,5,2);
			screen.combine(screen.buffer, measure, result);
			screen.clearBuffer(strlenCustom(measure),measure);
			screen.floatToChar(rfdata, measure,5,2);
			unsigned char extend[20] = "rf:";
			screen.combine(result, extend, result);
			screen.combine(result,measure,result);
			screen.setRowPlace(1,0);
			//setRowPlace(1,0);
			screen.set(1,result);
			screen.clearBuffer(strlenCustom(screen.buffer),screen.buffer);
			//SplitResult bf2 = screen.split(screen.buffer,0);
			SplitResult bf2=split(screen.buffer,0);
			unsigned char temp[10] = "DATA:";
			screen.combine(bf2.part1,temp, screen.buffer);
			test_delay(100);
		}
		//*/
		//*
		
		uint16_t rfvalue = adc_read(2);
		#ifdef ARDUINO
			//Serial.println(voltage);
			//test_delay(10);
		#endif
		
		//*/
		/*
		// tests previous value to previous measurement and if it is larger, returns that, otherwise returns previous highest value.
		float rfvolts = measurement(rfvalue, voltage); 
		if(rfvolts == rfvalue) {
			// no need to update display
			rf_meas_counter++;
		}
		else {
			// print rfvolts to display.
			unsigned char text[16] = "test:";
			unsigned char rfIntValue[5] = "";
			screen.clear();
			screen.intToChar(rfvolts, rfIntValue, 5);
			screen.combine(text, rfIntValue, text);
			screen.set(1, text);
			rf_meas_counter++;
		}		
		if(rf_meas_counter > 200) {
			rf_meas_counter = 0;
			reset_measurement();	// if value of meas_counter is over 200, resets the highest previous value to 0.00
		}
		//*/
    }
	
	return 0;
}

void test_delay(uint8_t ms) {
	#ifndef ARDUINO
		delay_ms(ms);
	#endif
	#ifdef ARDUINO
		delay(ms);
	#endif

}