float voltage, voltage2;
int sensorValue1, sensorValue2;
int onCycle, offDelay;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  onCycle=200;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  sensorValue1=analogRead(A0);
  sensorValue2=analogRead(A1);
  voltage= sensorValue1*(5.000/1023.000);
  voltage2= sensorValue2*(5.000/1023.000);
  delay(onCycle - offDelay);
  Serial.print(voltage);
  Serial.print("  ");
  Serial.print(voltage2*10);

  delay(offDelay);

  if(voltage < 2.30) {
    if(offDelay>0) {
      offDelay=offDelay-10;
    }
  }
  else{
    if(offDelay<200) {
      offDelay=offDelay+10;
    }
    
  }
  Serial.print(" Offdelay: ");
  Serial.print(offDelay);
  Serial.println();
}