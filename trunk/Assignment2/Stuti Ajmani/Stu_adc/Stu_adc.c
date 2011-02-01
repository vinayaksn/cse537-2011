#include <avr/io.h> 
#include <string.h>
#include <stdio.h>
#include "delay_x.h"
#define F_CPU 16000000UL
#include "lcd.h" 
#include "lcd.c" 
#include <stdlib.h>
//#include <avr/pgmspace.h>


// char* to_string(uint8_t num);


int main (void) 
{
	char value[100];
	char temp[100];	

	//DDRD = 1; //For powering the thermistor
	//PORTD = 1;

   unsigned int high,low,aval;
   lcd_init(LCD_DISP_ON);   /* initialize display, cursor off */ 
   _delay_ms(100);     

   // initializing registers for ADC
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
	
   // No MUX values needed to be changed to use ADC0 
   ADCSRA |= (1 << ADEN);  // Enable ADC 
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
   _delay_ms(100);     

   for(;;)  // Loop Forever 
   { 
      if(ADCH < 128) 
      { 
         	lcd_clrscr();           /* clear the screen*/ 
         	_delay_ms(1000);
		
  			 low = ADCL;		//Make certain to read ADCL first, it locks the values
  			 high = ADCH;		//and ADCH releases them.

	  		 aval = (high << 8) | low;
    	     itoa((int)aval, value, 10);
			 //itoa((int)aval, value, 10);
	   			
	   		 lcd_puts(value);  /* displays the string on lcd*/ 
         	 _delay_ms(1000);
			 unsigned int x= aval/2;
			 itoa((int)x, temp, 10);
			 lcd_puts(temp);  /* displays the string on lcd*/ 
         	 _delay_ms(1000);
       
	  } 

      else 
      { 
			 lcd_clrscr();                   /* clear the screen*/ 
    	     _delay_ms(1000);
			 lcd_puts("can't disp");  /* displays the string on lcd*/ 
    		 _delay_ms(10000); 
      } 

   } 

  return 0;
} 

