// Esimerkkin� h tiedoston tekemiseen.
#ifndef RF_ADC_H
#define RF_ADC_H

#ifndef ARDUINO
  #include <xc.h>
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
volatile uint8_t duty_cycle = 0;
volatile uint8_t duty_cycle2 = 0;
// Introduce all functions
void timer_init();
void adc_init();
uint16_t adc_read(uint8_t);
float get_input_voltage(uint8_t);

void timer_init() {
  uint16_t top_value=255;
  cli();
  DDRB|= (1<<PB5); //| (1<<PB6);
  TCCR1A= (1<<COM1A1)| (1<<COM1B1) |(1<<WGM11);
  TCCR1B= (1<<WGM13)|(1<<WGM12) | (1<<CS11);

  ICR1= top_value;

  OCR1A= (ICR1*duty_cycle) / 100;
  //OCR1B = (ICR1 * duty_cycle2) / 100;
  TIMSK1 |= (1<<OCIE1A);

  sei(); // Enable global interrupts
}

void adc_init() {
	// � Six Multiplexed Single Ended Input Channels
	// Will need to double check this with 1MHz clock timing.
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
}

uint16_t adc_read(uint8_t pin) {
  cli();
  pin &= 0x0F;
  ADMUX = (ADMUX & 0xF0) | pin;
  ADMUX |= (1 << REFS1) | (1 << REFS0); 
  ADCSRA |= (1 << ADSC);  
  while (ADCSRA & (1 << ADSC));
  sei();
  return ADC;  
	
}

float get_input_voltage(uint8_t pin) {
	uint16_t adc_value = adc_read(pin);  // Read ADC channel 0
	float voltage = adc_value *  (1.1/ 1023.0);  // Convert ADC to voltage
	return (120.99/21.99)*voltage;  // Scale back to input voltage
}

#endif