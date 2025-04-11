const int analogPinA1 = A1;
const int analogPinA3 = A3;
const int analogPinA5 = A5;

const float referenceVoltage = 3.3;
const int adcMax = 1023;
const int sampleCount = 100;

void setup() {
  Serial.begin(115200);
  analogReference(DEFAULT); // 3.3V on 3.3V Arduinos, 5V otherwise
  delay(1000);
  Serial.println("Starting multi-point voltage scan...");
}

void loop() {
  // === A1 Sampling Block ===
  int raw;
  int minVal = 1023;
  int maxVal = 0;
  long sum = 0;

  for (int i = 0; i < sampleCount; i++) {
    raw = analogRead(analogPinA1);
    sum += raw;
    if (raw < minVal) minVal = raw;
    if (raw > maxVal) maxVal = raw;
  }

  float avg = (sum / (float)sampleCount) * referenceVoltage / adcMax;
  float vMin = minVal * referenceVoltage / adcMax;
  float vMax = maxVal * referenceVoltage / adcMax;

  Serial.print("A1 Avg: ");
  Serial.print(avg, 3);
  Serial.print(" V | Min: ");
  Serial.print(vMin, 3);
  Serial.print(" V | Max: ");
  Serial.print(vMax, 3);
  Serial.println(" V");

  // === A3 - A5 Differential Reading ===
  int valA3 = analogRead(analogPinA3);
  int valA5 = analogRead(analogPinA5);

  float voltageA3 = valA3 * referenceVoltage / adcMax;
  float voltageA5 = valA5 * referenceVoltage / adcMax;
  float voltageDiff = voltageA3 - voltageA5;

  Serial.print("A3: ");
  Serial.print(voltageA3, 3);
  Serial.print(" V | A5: ");
  Serial.print(voltageA5, 3);
  Serial.print(" V | ΔV (A3 - A5): ");
  Serial.print(voltageDiff, 3);
  Serial.println(" V");

  Serial.println("-------------------------");

  delay(500); // Adjust as needed
}
