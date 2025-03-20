void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int sensor_value1=analogRead(A0);
  int sensor_value2=analogRead(A1);
  float voltage= sensor_value1*(5.000/1023.000);
  float voltage2= sensor_value2*(5.000/1023.000);
  
  Serial.print(voltage);
  Serial.print("  ");
  Serial.println(voltage2);


}
