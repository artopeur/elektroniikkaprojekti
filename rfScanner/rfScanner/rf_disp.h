/* rf_disp.h

*/
#ifndef RF_DISP_H
#define RF_DISP_H

#include <avr/io.h>
#include <xc.h>

#include "rf_I2C.h"

void initDisp();
void setText(uint8_t row, unsigned char*);
void setbacklight(volatile uint8_t backlight);

void initDisp() {
	initI2C();
	
}

void setText(uint8_t row, unsigned char *chars) {
	
	write_data(chars, sizeof(chars));
	
}

void setbacklight(volatile uint8_t backlight) {
	
}

#endif