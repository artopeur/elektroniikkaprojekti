/*
	I2C prescaled to 130 Hz clock.
	Usage: initI2C()->start_transmission()->write_data(&variable)->stop_transmission()
	Will be used by rf_lcd.h
	Doesn't support reading yet. To be continued.
*/
#ifndef RF_I2C_H
#define RF_I2C_H

// Arduino includes
///*
#include <inttypes.h>
#include <arduino.h>
//*/
/*
#include <stdint.h>		// uint8_t etc.
#include <avr/io.h>		// Registers for IO ports.
#include <string.h>
//*/
void initI2C();
void start_transmission();
void stop_transmission();
void write_data(unsigned char*, size_t);
unsigned char write_i2c(unsigned char*);
unsigned char write_command(unsigned char*);
//void read_data(

// Define slave address

#define SLAVE_ADDR 0x78
// defining commands
#define COMMAND 0x00
#define DATA 0x40

// Sender definitions, with receiving ACK

#define START 08
#define MT_SLA_ACK 18
#define MT_SLA_NACK 20
#define MT_DATA_ACK 32
#define MT_DATA_NACK 30

// Receiver definitions with writing ACK
#define RECEIVER_READY_ACK 40
#define RECEIVER_NACK 48
#define RESPONSE_ACK 50
#define END_RECEIVE_ACK 58

void initI2C() {
	
	// 0xB9 TWSR0 7:0 TWS7 TWS6 TWS5 TWS4 TWS3 [ ] TWPS[1:0]
	//TWSR0 = (1 << TWPS1) | (1<< TWPS0);		// Prescaler values, 11 = 64, 10 = 16, 01 = 4, 00 = 1
  // arduino
  TWSR = (1 << TWPS1) | (0<<TWPS0); // prescalers
	
	// 0xB8 TWBR0 7:0		TWBRn TWBRn TWBRn TWBRn TWBRn TWBRn TWBRn TWBRn
	//TWBR0 = 120;							// SCL FREQ = CPU_CLK / (16+2(TWBR)*(prescalerValue))		Gives 130 Hz clock
	//arduino
  TWBR = 180;                 // 518 hz prescaler 16
    // 0xBC TWCR0 7:0 TWINT TWEA TWSTA TWSTO TWWC TWEN [ ] TWIE
	//TWCR0 = (1 << TWINT);					// Reset lane with TWINT, set's value to 1.
	// arduino
  TWCR = (1 << TWINT);
}

void start_transmission() {
    TWCR = (1 << TWINT) | (1<<TWSTA) | (1 << TWEN);	// Start condition
    while(!(TWCR & (1 <<TWINT)));						// wait for flag to set (transmission of start condition)
}

void stop_transmission() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);	// Stop the transmission, No need to wait for ack or nack.
}

void write_data(unsigned char *data, size_t len, uint8_t row) {

	// required data length is 20 characters / row, max set to 255
  uint8_t retries = 5;
  unsigned char ack=0;
	start_transmission();
  ack = write_command((SLAVE_ADDR));    // clear screen
  ack = write_command(0x80);
  ack = write_command(0x01);
  stop_transmission();
  delay(10);
  //*
  start_transmission();
  if(row == 1) {
    ack = write_command((SLAVE_ADDR)); // change address.
    ack = write_command(0x80);
    ack = write_command(0x01);
    
  }
  else {
    ack = write_command((SLAVE_ADDR)); // change address
    ack = write_command(0x80);
    ack = write_command(0xA8);
  }
  stop_transmission();
  delay(10);
  //*/
  //ack = write_command(0x08);
  Serial.print("The size of data is: ");
  Serial.println(len);
  Serial.println("beginning write.");

  start_transmission();                 // start connection
  ack = write_command((SLAVE_ADDR));
  Serial.println(ack);

  ack = write_command(0x40);
  
  Serial.print("Send data, response is: ");
  Serial.println(ack);
  for(int8_t i=0;i<20;i++){
    ack = write_command(data[i]);					// write byte from data array to the display.
  }	
  	stop_transmission();                  // end the connection, send stop.						
}

unsigned char write_command(unsigned char *data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1<<TWEN);
  while(!(TWCR & (1<<TWINT)));
  return (TWSR & 0xF8);
}
unsigned char write_i2c(unsigned char *data) {
    TWDR = data;									// set current byte as data
    TWCR = (1 <<TWINT) | (1<<TWEN);				// write to lane
	while (!(TWCR & (1<<TWINT)));					// wait for ack or nack
	return (TWSR & 0xF8);							// Return top 5 bits of TWSR0, where the status is kept. (Gives the start, sla, data ack and nack codes.)
}

#endif