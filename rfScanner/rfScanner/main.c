/*
 * main.c
 *
 * Created: 3/22/2025 12:58:42 PM
 *  Author: artop, tuomast, attek
 */ 

//Defines
#define F_CPU 16000000UL // 1 MHz

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

//*
ISR(TIMER1_COMPA_vect)
{
  OCR1A = (ICR1* duty_cycle)/100;
  OCR1B = (ICR1* duty_cycle2)/100;
}
//*/
//*
ISR(TIMER3_COMPA_vect) {
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
	uint8_t rf_meas_counter = 0;
	
	adc_init();
	timer_init();
	init_timer3(); //stops interrupts before setting timer3, enables interrupts after that.
	//test_delay(10);

	initI2C();
	initDisp();
	test_delay(100);

    while(1)
    {
		#ifdef ARDUINO
			Serial.println("Testing");
			test_delay(100);
		#endif
		//*
		unsigned char buffer[20] = "data:";
		unsigned char measure[20] = "";
		volatile float data = 0.1;
		volatile float rfdata = 0.11;
		clearScreen();
		//*
		//setText(1,buffer);
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
			floatToChar(data,measure,5,2);
			combine(buffer, measure, result);
			clearBuffer(strlenCustom(measure),measure);
			floatToChar(rfdata, measure,5,2);
			char extend[20] = "rf:";
			combine(result, extend, result);
			combine(result,measure,result);
			setRowPlace(1,0);
			setText(1,result);
			clearBuffer(strlenCustom(buffer),buffer);
			SplitResult bf2=split(buffer,0);
			char load[20] = "DATA:";
			combine(bf2.part1,load, buffer);
			test_delay(500);
		}
		//*/
		//*
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
			unsigned char text[16] = "test text";
			
			setText(1, text);
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