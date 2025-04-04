/*
	RF Measurement code
	Does not require inputs and outputs, but requires int8_t, int16_t
	So needs to have that in the library includes.

*/


float measurement(uint16_t, float);
void reset_measurement(void);

volatile float previous = 0.00;

float measurement(uint16_t value, float reference) {
	
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
