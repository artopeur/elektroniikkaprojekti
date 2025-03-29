// Include timer3 initialization
#include <avr/io.h>
#include <avr/interrupt.h>
// global variables
volatile uint16_t timer_count = 0;	// maximum of 65 536 ms

void init_timer3(void);
void delay_ms(uint16_t);

void init_timer3(void) {
	cli(); // disable interrupts globally
	TCCR3B |= (1 << WGM32);		// Timer3 WGM32 enabled. Leave other bits intact.
	OCR3A = 124;				//  1 000 000 / 8 = 125 000 -> 125 000 / 1000 us = 125 ticks / ms -> 125 -1 = 124 ticks.
	TCCR3B |= (1 << CS31);		// prescaler set to 8  || leave other bits intact, just set CS31
	TIMSK3 |= (1 << OCIE3A);	// interrupt enabled for the timer3 and just set bit OCIE3A
	sei();						// enable interrupts globally
}

void delay_ms(uint16_t ms) {
	uint16_t start = timer_count;
	while ((timer_count - start) < ms); // wait for the specified time.
}