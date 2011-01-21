#define F_CPU 16000000UL // This is the frequency of the compiler.
#include <avr/io.h> //For input and output
#include "lcd.h"
#include "delay_x.h" //"" means that it will search in the current directory


int main()
{
   
   lcd_init(LCD_DISP_ON);   
    while (1)              
       {                           
           lcd_clrscr();             
           lcd_puts("Vibhas Kumar");  
           _delay_ms(50);
        }    
   return 1;
}
 
