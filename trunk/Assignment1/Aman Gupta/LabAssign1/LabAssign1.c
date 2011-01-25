#define F_CPU 16000000UL
#include <avr/io.h>
#include "delay_x.h"
#include "lcd.h"
#include "lcd.c"

int main(void)
{
	lcd_init(LCD_DISP_ON);
	while (1)
		{
			lcd_clrscr();
			lcd_puts("Aman Gupta");
			_delay_ms(50);

			for(int i=0;i<16;i++)
				{
					lcd_command(LCD_MOVE_DISP_RIGHT);
					_delay_ms(900);
				} 

		}
}
