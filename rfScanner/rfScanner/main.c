/*
 * main.c
 *
 * Created: 3/22/2025 12:58:42 PM
 *  Author: artop, tuomast, attek
 */ 

//Defines
#define F_CPU 16000000UL // 16 MHz
//#define F_CPU 2000000UL // 2 MHz
	


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
void timer_init();
void adc_init();
uint16_t adc_read(uint8_t);


//Global variables
//volatile float voltage= 0.00;
//volatile float voltage2= 0.00;
volatile uint16_t voltage = 0;
volatile uint16_t voltage2 = 0;
volatile uint16_t adccount = 0;

volatile uint8_t duty_cycle = 50;
volatile uint8_t duty_cycle2 = 50;
volatile uint16_t display_counter = 0;

//*
ISR(TIMER1_COMPA_vect)
{

	//voltage= get_input_voltage(0);
	//voltage2= get_input_voltage(1);


}
//*/
//*
ISR(TIMER2_COMPA_vect) {
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
		Serial.println("test");
		//initI2C();
		//init_timer3();
		//Serial.println("init done.");
		//delay(20);
		//initDisp();
		//delay(30);
		
		//delay(100);
		
		
	#endif
	uint16_t rf_meas_counter = 0;
	
	// From page 62 / 294, the unconnected pins to save power consumption. They are floating after reset.
	// Unused ports of port D
	//DDRD = 0x00;
	//PORTD = 0xFF; //set pull-up functionality.

	// PB0
	//DDRB &= ~(1 << PB0);
	//PORTB |= (1 << PB0);

	// ADC6, ADC7 If they are available.
	//DDRC &= ~((1 << PC6) | (1 << PC7));        // Set PC6 and PC7 as input
    //PORTC |= (1 << PC6) | (1 << PC7);          // Enable pull-ups on PC6 and PC7
	init_timer3(); //stops interrupts before setting timer3, enables interrupts after that.
	
	adc_init();
	#ifdef ARDUINO
		Serial.println("---ADC INIT DONE----");
	#endif
	test_delay(1000);
	//timer_init(); // STOPS ALL ACTIVITY WHEN
	
	#ifdef ARDUINO
		Serial.println("----TIMER INIT DONE----");
		test_delay(1000);
	#endif

	initI2C();
	#ifdef ARDUINO
		Serial.println("----I2C INIT DONE----");
		test_delay(1000);
	#endif

	timer_init();
	#ifdef ARDUINO
		Serial.println("----BUCK INIT DONE----");
		test_delay(1000);
	#endif
	initDisp();
	#ifdef ARDUINO
		Serial.println("----DISP INIT DONE----");
		test_delay(1000);
	#endif

	uint8_t i=0;
    while(1)
    {
		
		voltage = adc_read(0);
		
		//OCR1B = (ICR1* duty_cycle2)/100;
		//*
		if(voltage>60)
		{
			if(duty_cycle<100){
				duty_cycle+=1;
			}
		}
		if(voltage<60)
		{
			if(duty_cycle>0){
				duty_cycle-=1;
			}
		}
		OCR1A = (ICR1* duty_cycle)/100;
		//*/
		//*/
		/*
		if(voltage2<119)
		{
			if(duty_cycle2<100)duty_cycle2+=1;
		}
		if(voltage2>119)
		{
			if(duty_cycle2>0)duty_cycle2-=1;
		}
		

		//test_delay(10);
		/*if(adccount >= 100) {
			adccount = 0;
		}
		*/
			
			//delay(1);
		//*

		/*
		unsigned char start[10] = "data:";
		//clearBuffer(strlenCustom(start),start);
		//setText(2,start);
		
		unsigned char measure[20] = "";
		volatile int data = 1;
		volatile int rfdata = 11;
		//screen.clear();
		#ifdef ADRUINO
			Serial.println("Testing");
		#endif
		//*/
		
		//test_delay(10);

		/*
		if(i<50)
		{
			//data = adc_read(0);
			if(i < 25) {
				//data = data +1;
				rfdata = rfdata+11;
			}
			else {
				//data=data - 1;
				rfdata=rfdata-11;
			}
			i++;
		}
		test_delay(10);
		*/
		display_counter++;
		if (display_counter >= 5000) { // 250 loops × 2ms = 500ms
			display_counter = 0;

			unsigned char start[10] = "data:";
			unsigned char measure[20] = "";
			unsigned char result[30] = "";

			intToChar(voltage, measure, 10);  // Convert voltage to char array
			combine(start, measure, result);  // Combine "data:" + voltage
			setText(1, result);  // Update display

			// You can also print duty cycle if you want
			#ifdef ARDUINO
				Serial.print("Duty cycle: ");
				Serial.println(duty_cycle);
			#endif
			
			#ifdef ARDUINO
				Serial.println(voltage);
				test_delay(1);
			#endif
		}
		
		/*
		clearBuffer(strlenCustom(measure),measure);
		unsigned char result [20] = "";
		intToChar(data,measure,10);
		combine(start, measure, result);
		//clearBuffer(strlenCustom(measure),measure);
		//intToChar(rfdata, measure,5);
		//unsigned char extend[20] = " rf: ";
		//combine(result, extend, result);
		//combine(result,measure,result);
		//setRowPlace(1,0);
		setText(1,result);
		//clearBuffer(strlenCustom(measure), result);
		//SplitResult bf2 = split(buffer,0);
		//SplitResult bf2=split(result,0);
		//unsigned char temp[10] = "DATA:";
		//combine(bf2.part1,temp, result);
		//test_delay(10);
		if(i==49) {
			i=0;
		}
		//*/
				/*
		setText(1,buffer);
		//*/
		/*
		uint16_t rfvalue = adc_read(3);
		//voltage = adc_read(1);
		//voltage2 = adc_read(2);

		/*
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
		delay_ms(ms);
	#endif

}

void timer_init() {
	cli();
	uint16_t top_value=199;
	DDRB|= (1<<PB1) | (1<<PB2);
	#ifdef ARDUINO
	  TCCR1A= (1<<COM1A1)|(1<<WGM11);
	  TCCR1B= (1<<WGM13)|(1<<WGM12) | (1<<CS11);
	#endif
	#ifndef ARDUINO
	  // poistettu välistä (1<<COM1B1)
	  TCCR1A= (1<<COM1A1)| (1<<WGM11);
	  TCCR1B= (1<<WGM13)|(1<<WGM12) | (1<<CS11);
  
	  ICR1= 199;
  
	#endif
	OCR1A= (ICR1* duty_cycle) / 100;
	//OCR1B = (ICR1 * duty_cycle2) / 100;
	//TIMSK1 |= (1<<OCIE1A); // Removed because timer handling takes too much time.
	// Stops using the processing power.
	
	sei(); // Enable global interrupts
  }
  
void adc_init() {
	// moved so don't need to rechange the reference from 1.1 volts.
  ADMUX |= (1 << REFS1) | (1 << REFS0); 
  
  // � Six Multiplexed Single Ended Input Channels
	// Will need to double check this with 1MHz clock timing. (2MHz clock, prescaler 32 :: Gives  2Mhz /32 = 62.5kHz...)
  // Should be ok now.. A bit faster A/D
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
  
  // ADDING enabling adc
  ADCSRA |= (1 << ADEN);

}

uint16_t adc_read(uint8_t pin) {
  
  pin &= 0x0F;  // Mask to lower 4 bits
  uint8_t admux_saved = ADMUX & 0xF0; // Save reference voltage bits
  ADMUX = admux_saved | pin;           // Set the channel without touching reference bits
  ADCSRA |= (1 << ADSC);  
  while (ADCSRA & (1 << ADSC));
  
  return ADC;  
	
}