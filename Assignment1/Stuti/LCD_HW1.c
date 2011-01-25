#define F_CPU 16000000UL
#include "delay_x.h"
#include <avr/io.h> 
//#include <util/delay.h> 
#include "lcd.h" 
#include "lcd.c" 

int main(void) 
{    
  lcd_init(LCD_DISP_ON);   /* initialize display, cursor off */ 
    while (1)               /* loop forever */ 
       {                            
    lcd_clrscr();                   /* clear the screen*/ 
    _delay_ms(1000); 
    lcd_puts("Stuti");  /* displays the string on lcd*/ 
    _delay_ms(1000); 
        }   
		return 0; 
} 	
