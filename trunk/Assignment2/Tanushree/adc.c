#define F_CPU 16000000UL

#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include "lcd.h"
#include "lcd.c"

int main (void) 
{ 
unsigned int x;
char t[100];
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 

   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
   ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading 

   // No MUX values needed to be changed to use ADC0 

   //ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode 

   ADCSRA |= (1 << ADEN);  // Enable ADC 
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions 

   for(;;)  // Loop Forever 
   { 
      // TODO: Test ADC Value and set LEDs 

      lcd_init(LCD_DISP_ON);

		lcd_clrscr();
		_delay_ms(1000);

		x= ADC;
    	t= itoa((int)x,t,10);
		lcd_puts(t);
		_delay_ms(1000);

   } 
} 
