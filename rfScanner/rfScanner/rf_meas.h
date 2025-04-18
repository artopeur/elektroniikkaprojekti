/*
	RF Measurement code
	Does not require inputs and outputs, but requires int8_t, int16_t
	So needs to have that in the library includes.

*/

#ifndef RF_MEAS_H
#define RF_MEAS_H

#define RF_NOISE_FLOOR 12
#define RF_MAX_SIGNAL 255

#ifndef ARDUINO
	#include <stdint.h>
#endif

float measurement(uint16_t, float);
void reset_measurement(void);

static volatile float previous = 0.00;

float measurement(uint16_t value, float reference) {
	
	if(value < RF_NOISE_FLOOR) return 0.00;
	
	float volts = value / reference;
	if (previous > volts) {
		return previous;
	}
	else {
		previous = volts;
		return volts;
	}
	return -1;
}


void reset_measurement(void) {
	previous = 0.00;
}

#endif