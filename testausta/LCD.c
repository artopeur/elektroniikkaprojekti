#define SDA_PIN A4  // Arduino's default SDA pin
#define SCL_PIN A5  // Arduino's default SCL pin

#define SLAVE_ADDR 0x78  // LCD slave address
#define COMMAND 0x00      // Command prefix
#define DATA 0x40         // Data prefix

void I2C_Start() {
  pinMode(SDA_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
  
  digitalWrite(SDA_PIN, HIGH);
  digitalWrite(SCL_PIN, HIGH);
  digitalWrite(SDA_PIN, LOW);
  digitalWrite(SCL_PIN, LOW);
}

void I2C_Stop() {
  digitalWrite(SDA_PIN, LOW);
  digitalWrite(SCL_PIN, LOW);
  digitalWrite(SCL_PIN, HIGH);
  digitalWrite(SDA_PIN, HIGH);
}

void I2C_out(unsigned char data) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(SDA_PIN, (data & 0x80) ? HIGH : LOW);
    digitalWrite(SCL_PIN, LOW);
    digitalWrite(SCL_PIN, HIGH);
    digitalWrite(SCL_PIN, LOW);
    data <<= 1;
  }

  digitalWrite(SDA_PIN, HIGH); // ACK
  digitalWrite(SCL_PIN, HIGH);
  while (digitalRead(SDA_PIN) == HIGH);
  digitalWrite(SCL_PIN, LOW);
}

void lcd_init() {
  I2C_Start();
  I2C_out(SLAVE_ADDR);
  I2C_out(COMMAND);
  I2C_out(0x38);
  delay(10);
  I2C_out(0x39);
  delay(10);
  I2C_out(0x14);
  I2C_out(0x78);
  I2C_out(0x5E);
  I2C_out(0x6D);
  I2C_out(0x0C);
  I2C_out(0x01);
  I2C_out(0x06);
  delay(10);
  I2C_Stop();
}

void lcd_send_data(unsigned char data) {
  I2C_Start();
  I2C_out(SLAVE_ADDR);
  I2C_out(DATA);
  I2C_out(data);
  I2C_Stop();
}

void lcd_send_string(const char *text) {
  I2C_Start();
  I2C_out(SLAVE_ADDR);
  I2C_out(DATA);
  
  while (*text) {
    I2C_out(*text++);
  }
  
  I2C_Stop();
}

void setup() {
  pinMode(SDA_PIN, OUTPUT);
  pinMode(SCL_PIN, OUTPUT);
  
  lcd_init();
  lcd_send_string("Hello LCD");
}

void loop() {
}
