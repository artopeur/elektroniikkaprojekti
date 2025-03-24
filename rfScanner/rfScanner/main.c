/*
 * main.c
 *
 * Created: 3/22/2025 12:58:42 PM
 *  Author: artop
 */ 

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//Defines
#define F_CPU 1000000


//Global variables
volatile uint16_t timer_count = 0;

void timer_init() {
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);  // CTC mode, Prescaler 64
	OCR1A = (F_CPU / 64 / 1000) - 1;  // Set compare value for 1ms
	TIMSK1 |= (1 << OCIE1A);  // Enable compare match interrupt
	sei();  // Enable global interrupts
}

ISR(TIMER1_COMPA_vect) {
	timer_count++;
}

int main(void)
{
	adc_init();
	timer_init();
	pause_ms(25); 
    while(1)
    {
		float val = get_input_voltage();
		
        //TODO:: Please write your application code
    }
}

void adc_init() {
	// • Six Multiplexed Single Ended Input Channels
	// Will need to double check this with 1MHz clock timing.
	ADMUX = (1 << REFS0);  // Select AVCC as reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, Prescaler = 64
}

uint16_t adc_read(uint8_t channel) {
	
}

float get_input_voltage() {
	uint16_t adc_value = adc_read(0);  // Read ADC channel 0
	float voltage = (adc_value * 10) / 1023.0;  // Convert ADC to voltage
	return voltage * 10;  // Scale back to input voltage
}

void pause_ms(uint16_t ms) {
	// Double check with ms counting.
	timer_count = 0;
	while (timer_count < ms);
}