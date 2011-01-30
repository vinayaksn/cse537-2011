
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include "delay_x.h"
#include "lcd.h"
#include "lcd.c"

#include <avr/interrupt.h> 


int main (void) 
{ 
   //DDRD |= (1 << 7); // Set LED1 as output 
  // DDRG |= (1 << 0); // Set LED2 as output 
  DDRD =140;

   
 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 

   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
   ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading 
   ADMUX |= (1 << ADLAR);
   
  
lcd_init(LCD_DISP_ON);
   _delay_ms(1000);
   lcd_clrscr();
   _delay_ms(1000);

   //lcd_command( (1<<LCD_MOVE) | (1<<LCD_MOVE_RIGHT) );
   _delay_ms(10);
      
   

for(;;)  // Loop Forever 
   { 
   
   
     /* if(ADCH < 128) 
      { 
         lcd_clrscr();
	  _delay_ms(1000);	  
      lcd_puts("1");	  
	  _delay_ms(1000);
    ADCSRA |= (1 << ADEN); 
   ADCSRA |= (1 << ADSC); 
         
      } 

      else 
      { 
         
         lcd_clrscr();
	  _delay_ms(1000);	  
      lcd_puts("0");	  
	  _delay_ms(1000);
    ADCSRA |= (1 << ADEN); 
   ADCSRA |= (1 << ADSC); 
      } 
	  _delay_s(3);
	    ADCSRA |= (0 << ADEN); 
   ADCSRA |= (0 << ADSC); 
   */

  char buf[10];
	sprintf( buf, "%d\n", ADCH );
	

	                                                                    
         lcd_clrscr();
	  _delay_ms(1000);	  
	  
      lcd_puts(buf);	  
	  
	  _delay_ms(1000);
    ADCSRA |= (1 << ADEN); 
   ADCSRA |= (1 << ADSC); 
         
       
	  _delay_s(3);
	    ADCSRA |= (0 << ADEN); 
   ADCSRA |= (0 << ADSC); 

   }
    
}
