// Esimerkkin� h tiedoston tekemiseen.
#ifndef RF_ADC_H
#define RF_ADC_H

#ifndef ARDUINO
  #include <xc.h>
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif

// Introduce all functions
//void timer_init();

//float get_input_voltage(uint8_t);


/*
float get_input_voltage(uint8_t pin) {
	uint16_t adc_value = adc_read(pin);  // Read ADC channel 0
	float voltage = adc_value *  (1.1/ 1023.0);  // Convert ADC to voltage
	return (120.99/21.99)*voltage;  // Scale back to input voltage
}
*/
#endif