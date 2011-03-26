#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> 
#include "delay_x.h"
#include "lcd.h"
#include "lcd.c"
#include <stdlib.h>

int prev=0;
int count=0;
int start=0;

int main()
{

	DDRD=1;
	PORTD=1;


 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to (111)128 - 125KHz sample rate @ 16MHz 
 ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
  // ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading 

   // No MUX values needed to be changed to use ADC0 

   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode 
   ADCSRA |= (1 << ADEN);  // Enable ADC 

   ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt 
   sei();   // Enable Global Interrupts 

   ADCSRA |= (1 << ADSC);  // Start A2D Conversions 


  // lcd_init(LCD_DISP_ON);
   for(;;)
   {

   }
}

ISR(ADC_vect)
{

unsigned int val;
val =ADCL;
val |=(ADCH << 8);
lcd_init(LCD_DISP_ON);
// for stein-hart equation from wikipedia and values found from http://web.cecs.pdx.edu/~gerry/class/EAS199B/howto/thermistorArduino/thermistorArduino.pdf
char result[10];

itoa((int)val, result, 10);

if(start==0)
{
 start=1;
 prev=(int)val;
}
else if((int)val-prev>100)
 count++;

prev=(int)val;
lcd_puts(result);
}
