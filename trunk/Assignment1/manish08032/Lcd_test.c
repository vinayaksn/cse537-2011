
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"



int main()
{

   lcd_init(LCD_DISP_ON);
   _delay_ms(1000);
   lcd_clrscr();
   _delay_ms(1000);
      
   while(1)
   {      
      lcd_clrscr();
	  _delay_ms(1000);	  
      lcd_puts("Manish Dahamiwal!");	  
	  _delay_ms(1000);
	 

   }
   return 0;
}


