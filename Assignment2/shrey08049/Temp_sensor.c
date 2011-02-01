// References - http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=56429


#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"



int main()
{

	unsigned int adc_value;
	char value[10];
	char * val_print;

   lcd_init(LCD_DISP_ON);
   _delay_ms(1000);
   lcd_clrscr();
   _delay_ms(1000);

   

	DDRD=1;
	PORTD=1;
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz
	ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
   
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC
 //  ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading

   // No MUX values needed to be changed to use ADC0

   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
   ADCSRA |= (1 << ADEN);  // Enable ADC
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions

 
   while(1)
   {
   
   
    adc_value  = ADCL | (ADCH <<8) ;       
   	itoa(adc_value,value,10);
	val_print=value;
 	
	lcd_clrscr();
	  _delay_ms(1000);
      lcd_puts(val_print);	  
	  _delay_ms(1000);
   
   }
   return 0;
}
