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
//volatile float voltage= 0.00;
//volatile float voltage2= 0.00;
volatile uint16_t voltage = 0;
volatile uint16_t voltage2 = 0;
volatile uint16_t adccount = 0;

//*
ISR(TIMER1_COMPA_vect)
{

	//voltage= get_input_voltage(0);
	//voltage2= get_input_voltage(1);


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
		Serial.begin(115200);
		//initDisp();
		//Serial.println("test");
		initI2C();
		test_delay(20);
		initDisp();
		Serial.println("init done.");
		delay(100);
		
		
	#endif
	uint16_t rf_meas_counter = 0;
	
	// From page 62 / 294, the unconnected pins to save power consumption. They are floating after reset.
	// Unused ports of port D
	DDRD = 0x00;
	PORTD = 0xFF; //set pull-up functionality.

	// PB0
	//DDRB &= ~(1 << PB0);
	//PORTB |= (1 << PB0);

	// ADC6, ADC7 If they are available.
	//DDRC &= ~((1 << PC6) | (1 << PC7));        // Set PC6 and PC7 as input
    //PORTC |= (1 << PC6) | (1 << PC7);          // Enable pull-ups on PC6 and PC7
	init_timer3(); //stops interrupts before setting timer3, enables interrupts after that.
	adc_init();
	test_delay(10);
	timer_init(); // STOPS ALL ACTIVITY WHEN

	#ifdef ARDUINO
		Serial.println("ADC INIT DONE");
	#endif
	//uint16_t temp = adc_read(2);
	//test_delay(10);
	//temp = adc_read(3);
	test_delay(1);
	//timer_init();
	#ifdef ARDUINO
		Serial.println("TIMER INIT DONE");
	#endif
	//test_delay(1);
	
	test_delay(1);

	/*
	initI2C();
	
	initDisp();
	//*/
	//initI2C();

	test_delay(10);
	#ifdef ARDUINO
		Serial.println("I2C INIT DONE");
	#endif
	
	//test_delay(100);
	adc_init();
	test_delay(100);
    while(1)
    {
		test_delay(100);

		voltage = adc_read(1);
		voltage2 = adc_read(2);
		#ifdef ARDUINO
			Serial.println("timer1");
		#endif
	
		//*
		if(voltage>50)
		{
			if(duty_cycle<100)duty_cycle+=1;
		}
		if(voltage<50)
		{
			if(duty_cycle>0)duty_cycle-=1;
		}
		//*/
		//*
		if(voltage2<119)
		{
			if(duty_cycle2<100)duty_cycle2+=1;
		}
		if(voltage2>119)
		{
			if(duty_cycle2>0)duty_cycle2-=1;
		}
		
		OCR1A = (ICR1* duty_cycle)/100;
		OCR1B = (ICR1* duty_cycle2)/100;
		//test_delay(10);
		/*if(adccount >= 100) {
			adccount = 0;
		}
		*/
			
			//delay(1);
		
		#ifdef ARDUINO
			//Serial.println(voltage);
			//test_delay(1);
		#endif
		//*
		unsigned char start[6] = "data:";
		//screen.set(1,start);
		
		unsigned char measure[20] = "";
		uint16_t volts = 0;
		//volatile float data = 0.1;
		//volatile float rfdata = 0.11;
		//screen.clear();
		#ifdef ADRUINO
			Serial.println("Testing");
		#endif
		//test_delay(10);
		/*
		setText(1,buffer);
		//*/
		//*
		uint16_t rfvalue = adc_read(3);
		//voltage = adc_read(1);
		//voltage2 = adc_read(2);
		#ifdef ARDUINO

			Serial.print("RFval: ");
			Serial.println(rfvalue);
			Serial.print("voltage: ");
			Serial.println(voltage);
			Serial.print("voltage2: ");
			Serial.println(voltage2);
			Serial.print("      ADCcount: ");
			Serial.println(adccount);
			Serial.print("      DUTY Cycle:");
			Serial.println(duty_cycle);
			Serial.print("      DUTY Cycle2:");
			Serial.println(duty_cycle2);

		#endif
			//test_delay(10);
		
		//*/
		/*
		
			if(i < 25) {
				data = data + 0.1;
				rfdata = rfdata+0.11;
			}
			else {
				data=data - 0.1;
				rfdata=rfdata-0.11;
			}
			
			volts++;
			clearBuffer(strlenCustom(measure),measure);
			unsigned char result [20] = "";
			floatToChar(data,measure,5,2);
			combine(result, measure, result);
			clearBuffer(strlenCustom(measure),measure);
			floatToChar(rfdata, measure,5,2);
			unsigned char extend[20] = "rf:";
			combine(result, extend, result);
			combine(result,measure,result);
			setRowPlace(1,0);
			setRowPlace(1,0);
			setText(1,result);
			clearBuffer(strlenCustom(measure), result);
			SplitResult bf2 = screen.split(screen.buffer,0);
			SplitResult bf2=split(result,0);
			unsigned char temp[10] = "DATA:";
			combine(bf2.part1,temp, result);
			test_delay(10);
		
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