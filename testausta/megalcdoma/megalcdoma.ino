#include<Arduino.h>
#include "rf_I2C.h"
#include "rf_disp.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  //initDisp();
  Serial.println("test");
  initDisp();
  Serial.println("init done.");
  delay(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned char text1[20] = "taxi in the hub!";
  Serial.println("Beginning print to display.");
  setText(2,text1);
  Serial.println("setText is done.");
  delay(600);
}
