#define F_CPU 16000000UL
#include <avr/io.h>
#include "delay_x.h"
#include "lcd.h"
#include "lcd.c"

int main()
{
lcd_init(LCD_DISP_ON);
_delay_ms(100);
lcd_clrscr();
_delay_ms(100);
lcd_puts("Nikhil Singh");
_delay_ms(100);


while(1)
{



}
return 0;

}
