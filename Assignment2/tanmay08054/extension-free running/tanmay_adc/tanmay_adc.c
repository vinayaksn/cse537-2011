
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include "delay_x.h"
#include "lcd.h"
#include "lcd.c"

#include <avr/interrupt.h> 


int main (void) 
{ 

 // DDRD =140;
	int x=-1,y=-1;
   
 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 
ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
 

   ADMUX |= (0 << ADLAR);
  
  
  

	

	//ADCSRA |= (1 << ADSC);
	//ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADATE);

	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);       	
	
	
	lcd_init(LCD_DISP_ON);
   _delay_ms(1000);
   lcd_clrscr();
   _delay_ms(1000);

   _delay_ms(10);
      
   

while(1)  // Loop Forever 
   { 
   
  //_delay_s(3);
	x= ADCL; 
	x |= (ADCH<<8); //left shift 
	
  char buf[10];
	sprintf( buf, "%d\n", x );
	

	                                                                    
         lcd_clrscr();
	  _delay_ms(1000);	  
	  
      lcd_puts(buf);	  
	
	  _delay_ms(1000);
//	ADCSRA |= (1 << ADSC);       	  
	 _delay_ms(1000);

   }
    
}
