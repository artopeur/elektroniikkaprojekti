volatile float voltage, voltage2, prevVoltage;
int sensorValue1, sensorValue2;
int onCycle, offDelay;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  onCycle=200;
  pinMode(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(3,1);
  sensorValue1=analogRead(A0);
  sensorValue2=analogRead(A1);
  voltage= sensorValue1*(5.000/1023.000);
  voltage2= sensorValue2*(5.000/1023.000);
  delay(onCycle - offDelay);
  Serial.print(voltage);
  Serial.print("  ");
  Serial.print(voltage2*10);

  
  volatile float test = voltage-prevVoltage;
  
  if(voltage < 1.80 || test > 0.2) {
    if(offDelay>0) {
        offDelay=offDelay-10;
    }
  }
  else if(voltage > 2.30 || test < 0.2){
    if(offDelay<200) {
      offDelay=offDelay+10;
    }
  }
  prevVoltage = voltage;
  delay(offDelay);
  digitalWrite(3,0);

  Serial.print(" Offdelay: ");
  Serial.print(offDelay);
  Serial.println();
}