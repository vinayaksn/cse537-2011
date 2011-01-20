
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
   _delay_ms(100);
   lcd_clrscr();
   _delay_ms(100);

   //lcd_command( (1<<LCD_MOVE) | (1<<LCD_MOVE_RIGHT) );
   _delay_ms(10);
      
   while(1)
   {      
      lcd_clrscr();
	  _delay_ms(100);	  
      lcd_puts("Ashish Gupta");	  
	  _delay_ms(100);
	for(int i=0;i<16;i++)
	{lcd_command(LCD_MOVE_DISP_RIGHT);
	_delay_ms(500); 
   }
   }
   return 0;
}


