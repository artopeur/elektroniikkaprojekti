/* rf_disp.h

*/
#ifndef RF_DISP_H
#define RF_DISP_H

#include <avr/io.h>
#include <xc.h>

void initDisp();
void setText(uint8_t row, char *chars);
void setbacklight(volatile uint8_t backlight);

void initDisp() {
	
}

void setText(uint8_t row, char *chars) {
	
}

void setbacklight(volatile uint8_t backlight) {
	
}

#endif