#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
volatile uint8_t duty_cycle = 0;
volatile uint8_t duty_cycle2 = 0;
int main() {
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
    setup_timer1();
    while(true) {    
    int sensor_value1=readAnalog(0);
    int sensor_value2=readAnalog(1);
    float voltage= sensor_value1*(1.100/1023.000);
    float voltage2= sensor_value2*(1.100/1023.000);
    float actualVoltage= (120.99/21.59)*voltage;
    float actualVoltage2= (120.99/21.59)*voltage2
  if(actualVoltage>2.45)
    {
      if(duty_cycle<100)duty_cycle+=1;
    }
  if(actualVoltage<1.8)
    {
      if(duty_cycle>0)duty_cycle-=1;
    }
    if(actualVoltage>3.3)
    {
      if(duty_cycle2<100)duty_cycle2-=1;
    }
    if(actualVoltage<2.8)
    {
      if(duty_cycle2>0)duty_cycle2+=1;
    }
  

    }
  
    return 0;
}
   


int readAnalog(uint8_t pin )
{

  pin &= 0x0F;
  ADMUX = (ADMUX & 0xF0) | pin;
  ADMUX |= (1 << REFS1) | (1 << REFS0); 

  ADCSRA |= (1 << ADSC);  


  while (ADCSRA & (1 << ADSC)) {
    
  }

  
  return ADC;  
}

void setup_timer1()
{
  uint16_t top_value=49;

  DDRB|= (1<<PB1) | (1<<PB2);
  TCCR1A= (1<<COM1A1)| (1<<COM1B1) |(1<<WGM11);
  TCCR1B= (1<<WGM13)|(1<<WGM12) | (1<<CS10);

  ICR1= top_value;

  OCR1A= (ICR1*duty_cycle) / 100;
  OCR1B = (ICR1 * duty_cycle2) / 100;
  TIMSK1 |= (1<<OCIE1A);

  sei();
}

ISR(TIMER1_COMPA_vect)
{
  OCR1A = (ICR1* duty_cycle)/100;
  OCR1B = (ICR1* duty_cycle2)/100;
}