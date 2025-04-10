/* rf_disp.h

*/
#ifndef RF_DISP_H
#define RF_DISP_H

//#include <avr/io.h>
//#include <xc.h>
#include "rf_I2C.h"

#define SLAVE_ADDR 0x78


void initDisp();
void setText(uint8_t row, unsigned char*);
void setbacklight(volatile uint8_t backlight);

void initDisp() {
  uint16_t response;
  //Serial.println("response made");
	initI2C();
  //Serial.println("I2C initialized.");
  start_transmission();
  //Serial.println("Start transmission sent.");
  response = write_command(SLAVE_ADDR);
  //Serial.print("Slave Addr sent: Response is: ");
  //Serial.println(response);
  response = write_command(0x38);
  //Serial.print("0x38 sent: Response is: ");
  //Serial.println(response);
  delay(10);
  response=write_command(0x39);
  //Serial.print("0x39 sent: Response is: ");
  //Serial.println(response);
  delay(10);
  char data[7] = {0x14,0x78,0x5E, 0x6D, 0x0C, 0x01, 0x06};
  //Serial.print("data variable made, data is: ");
  //Serial.println(data);
  for(uint8_t n = 0; n<7;n++) {
    response = write_command(data[n]);
    //Serial.print("data is: ");
    //Serial.print(data[n]);
    //Serial.print(" and response is: ");
    //Serial.println(response);
  }
  delay(10);
	stop_transmission();
}

void setText(uint8_t row, unsigned char *chars) {
  uint16_t response;
  //response = write_command(0);
  write_data(chars, sizeof(chars), row);
	
}

void setbacklight(volatile uint8_t backlight) {
	
}

#endif