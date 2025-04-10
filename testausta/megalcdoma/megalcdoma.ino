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
  float v1 = 1.8;
  float v2 = 3.3;
  float vin = 3.8;
  unsigned char text1[20] = {"V1=v1,V2=v2,IN=V2"};
  unsigned char text2[20] = "run home dude..";
  Serial.println("Beginning print to display.");
  setText(2,text1);
  Serial.println("setText is done.");
  delay(3000);
  Serial.println("Beginning print to display.");
  setText(1, text2);
  Serial.println("setText is done.");
  delay(3000);
}
