#define F_CPU 16000000L
#include<avr/io.h>
#include "delay_x.h"
#include "lcd.h"
#include "lcd.c"

int main() 
{ 
lcd_init(LCD_DISP_ON);              
while (1)                         
{ 
lcd_clrscr();   
_delay_ms(1000);                    
lcd_puts("Prateek Gaur");              
_delay_ms(1000); 
} 
return 0;
} 
