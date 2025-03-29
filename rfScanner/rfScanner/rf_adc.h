// Esimerkkinä h tiedoston tekemiseen.

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// Introduce all functions
void timer_init();
void adc_init();
uint16_t adc_read(uint8_t);
float get_input_voltage();

void timer_init() {
	TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);  // CTC mode, Prescaler 64
	OCR1A = (F_CPU / 64 / 1000) - 1;  // Set compare value for 1ms
	TIMSK1 |= (1 << OCIE1A);  // Enable compare match interrupt
	sei();  // Enable global interrupts
}

void adc_init() {
	// • Six Multiplexed Single Ended Input Channels
	// Will need to double check this with 1MHz clock timing.
	ADMUX = (1 << REFS0);  // Select AVCC as reference
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, Prescaler = 64
}

uint16_t adc_read(uint8_t channel) {
	return 1;
}

float get_input_voltage() {
	uint16_t adc_value = adc_read(0);  // Read ADC channel 0
	float voltage = (adc_value * 10) / 1023.0;  // Convert ADC to voltage
	return voltage * 10;  // Scale back to input voltage
}

