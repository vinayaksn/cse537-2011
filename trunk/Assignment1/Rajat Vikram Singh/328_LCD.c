#define F_CPU 16000000UL
#include <avr/io.h>
#include "delay_x.h"
#include "lcd.h"


int main()
{   
  	lcd_init(LCD_DISP_ON);
 	lcd_clrscr();
	_delay_ms(100);       
    lcd_puts("Rajat Vikram Singh");
   	_delay_ms(100);
	return 0;
}
