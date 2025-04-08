/*
	I2C prescaled to 130 Hz clock.
	Usage: initI2C()->start_transmission()->write_data(&variable)->stop_transmission()
	Will be used by rf_lcd.h
	Doesn't support reading yet. To be continued.
*/
#ifndef RF_I2C_H
#define RF_I2C_H

#include <stdint.h>		// uint8_t etc.
#include <avr/io.h>		// Registers for IO ports.
#include <string.h>

void initI2C();
void start_transmission();
void stop_transmission();
void write_data(unsigned char*, size_t);
uint8_t write_i2c(uint8_t);
//void read_data(

// Define slave address

#define SLAVE_ADDR 0x78
// defining commands
#define COMMAND 0x00
#define DATA 0x40

// Sender definitions, with receiving ACK

#define START 0x08
#define MT_SLA_ACK 0x18
#define MT_SLA_NACK 0x20
#define MT_DATA_ACK 0x28
#define MT_DATA_NACK 0x30

// Receiver definitions with writing ACK
#define RECEIVER_READY_ACK 0x40
#define RECEIVER_NACK 0x48
#define RESPONSE_ACK 0x50
#define END_RECEIVE_ACK 0x58

void initI2C() {
	
	// 0xB9 TWSR0 7:0 TWS7 TWS6 TWS5 TWS4 TWS3 [ ] TWPS[1:0]
	TWSR0 = (1 << TWPS1) | (1<< TWPS0);		// Prescaler values, 11 = 64, 10 = 16, 01 = 4, 00 = 1
	
	// 0xB8 TWBR0 7:0		TWBRn TWBRn TWBRn TWBRn TWBRn TWBRn TWBRn TWBRn
	TWBR0 = 120;							// SCL FREQ = CPU_CLK / (16+2(TWBR)*(prescalerValue))		Gives 130 Hz clock
	
    // 0xBC TWCR0 7:0 TWINT TWEA TWSTA TWSTO TWWC TWEN [ ] TWIE
	TWCR0 = (1 << TWINT);					// Reset lane with TWINT, set's value to 1.
	
}

void start_transmission() {
    TWCR0 = (1 << TWINT) | (1<<TWSTA) | (1 << TWEN);	// Start condition
    while(!(TWCR0 & (1 <<TWINT)));						// wait for flag to set (transmission of start condition)
}

void stop_transmission() {
    TWCR0 = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);	// Stop the transmission, No need to wait for ack or nack.
}

void write_data(unsigned char *data, size_t len) {
	start_transmission();
	uint8_t retries = 5;
	uint8_t ack=0;
	ack = write_i2c((SLAVE_ADDR << 1) | 0);				// No error handling yet. 0x18 means success. Need to read from return value. 0 means write, 1 means read.

	for(int8_t i=0;i<len;i++){							// required data length is 16 characters / row, max set to 255
		do {											// try to send data 5 times, if nack happens, retries.
			ack = write_i2c(data[i]);					// write byte from data array to the display.
			retries--;
		}while(ack != MT_DATA_ACK && retries > 0);		// Waiting for MT_DATA_ACK, so try again if not passed through.
	}
	stop_transmission();								// end the connection, send stop.
}

uint8_t write_i2c(uint8_t data) {
    TWDR0 = data;									// set current byte as data
    TWCR0 = (1 <<TWINT) | (1<<TWEN);				// write to lane
	while (!(TWCR0 & (1<<TWINT)));					// wait for ack or nack
	return (TWSR0 & 0xF8);							// Return top 5 bits of TWSR0, where the status is kept. (Gives the start, sla, data ack and nack codes.)
}

#endif