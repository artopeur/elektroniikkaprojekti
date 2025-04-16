#include<Arduino.h>

#define ARDUINO 1
#ifdef ARDUINO
  #include "/GIT/elektroniikkaprojekti/rfScanner/rfScanner/rf_I2C.h"
  #include "/GIT/elektroniikkaprojekti/rfScanner/rfScanner/rf_disp.h"
  #include "/GIT/elektroniikkaprojekti/rfScanner/rfScanner/rf_adc.h"
  #include "/GIT/elektroniikkaprojekti/rfScanner/rfScanner/rf_delay_t3.h"
  #include "/GIT/elektroniikkaprojekti/rfScanner/rfScanner/rf_meas.h"
#endif
#ifndef ARDUINO
  #include "rf_I2C.h"
  #include "rf_disp.h"
#endif

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
  unsigned char buffer[20] = "data:";
  unsigned char measure[20] = "";
  volatile float data = 0.1;
  volatile float rfdata = 0.11;
  clearScreen();
  //setText(1,buffer);
  for (uint8_t i = 0; i<50;i++) {
    if(i < 25) {
      data = data + 0.1;
      rfdata = rfdata+0.11;
    }
    else {
      data=data - 0.1;
      rfdata=rfdata-0.11;
    }
    clearBuffer(strlenCustom(measure),measure);
    unsigned char result [20] = "";
    
    
    floatToChar(data,measure,5,2);
    combine(buffer, measure, result);
    clearBuffer(strlenCustom(measure),measure);
    floatToChar(rfdata, measure,5,2);
    combine(result, " rf:", result);
    combine(result,measure,result);
    setRowPlace(1,0);
    setText(1,result);
    clearBuffer(strlenCustom(buffer),buffer);
    SplitResult bf2=split(buffer,0);
    combine(bf2.part1,"DATA:", buffer);
    delay(500);
  }
  // put your main code here, to run repeatedly:
  /*unsigned char buffer[20] = {"                    "};
  unsigned char text1[20] = {"V1=v1,V2=v2,IN=V2"};
  unsigned char text2[20] = "run home dude..";
  float v1 = 1.8;
  floatToChar(v1, buffer, 5, 2);
  float v2 = 3.3;
  floatToChar(v2,buffer,5, 2);

  float vin = 3.8;
  floatToChar(vin,buffer,5,2);

  Serial.println("Beginning print to display.");
  clearScreen();
  setText(2,text1);
  Serial.println("setText is done.");
  delay(3000);
  
  Serial.println("Beginning print to display.");
  clearScreen();
  setRow(1);
  setText(1, text2);
  Serial.println("setText is done.");
  
  delay(3000);
  setRow(2);
  setText(2,buffer);
  delay(3000);
  int percent = 98;
  clearBuffer(20,buffer);
  intToChar(percent, buffer,3);
  setRowPlace(1,17);
  setText(1, buffer);
  delay(3000);
  */

}
