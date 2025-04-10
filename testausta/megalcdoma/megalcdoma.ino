#include<Arduino.h>
#include "rf_I2C.h"
#include "rf_disp.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  //initDisp();
  //Serial.println("test");
  initDisp();
  Serial.println("init done.");
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char buffer[20] = {"                    "};
  float v1 = 1.8;
  float_to_char(v1, buffer, 5, 2);
  float v2 = 3.3;
  float_to_char(v2,buffer,5, 2);

  float vin = 3.8;
  float_to_char(vin,buffer,5,2);


  unsigned char text1[20] = {"V1=v1,V2=v2,IN=V2"};
  unsigned char text2[20] = "run home dude..";
  Serial.println("Beginning print to display.");
  clear_screen();
  setText(2,text1);
  Serial.println("setText is done.");
  delay(3000);
  Serial.println("Beginning print to display.");
  clear_screen();
  setText(1, text2);
  Serial.println("setText is done.");
  delay(3000);
  setText(2,buffer);
  delay(3000);
  int percent = 98;
  for (uint8_t i=0;i<20;i++)  {   // clearing buffer. Might need to move to rf_disp.h to make a function for this.
    buffer[i] = ' ';
  }
  
  int_to_char(percent, buffer,3);
  setText(1, buffer);
  delay(3000);
}
