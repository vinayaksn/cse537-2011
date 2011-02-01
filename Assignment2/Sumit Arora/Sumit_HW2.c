#include <avr/io.h> 
#include "delay_x.h"
#define F_CPU 16000000UL
#include "lcd.h" 
#include "lcd.c" 


int main (void) 
{
   uint8_t high,low,aval;
   lcd_init(LCD_DISP_ON);   
   _delay_ms(100);     

   ADMUX = 0b01101000;
   ADCSRA = 0b11000111;
   _delay_ms(100);     

   for(;;)   
   { 
      if(ADCH < 128) 
      { 
        lcd_clrscr();  
        _delay_ms(1000);
		
  		low = ADCL;		//Make certain to read ADCL first, it locks the values
  		high = ADCH;		//and ADCH releases them.

  		aval = (high << 8) | low;
        lcd_puts(aval);
    	_delay_ms(10000); 
      
	  } 

   } 
} 



