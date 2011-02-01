#define F_CPU 16000000UL

#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/io.h>
#include "lcd.h"
#include "lcd.c"
int main()
{
 
lcd_init(LCD_DISP_ON);

while(1)
{
lcd_clrscr();
_delay_ms(1000);
lcd_puts("tanushree");
_delay_ms(1000);
}
return 0;
}
