/* rf_disp.h

*/
#ifndef RF_DISP_H
#define RF_DISP_H

#include <avr/io.h>
#include <xc.h>
#include "rf_I2C.h"

void initDisp();
void setText(uint8_t row, char[]);
void setbacklight(volatile uint8_t backlight);

void initDisp() {
	initI2C();
	
}

void setText(uint8_t row, char chars[255]) {
	
	write_data(chars);
	
}

void setbacklight(volatile uint8_t backlight) {
	
}

#endif