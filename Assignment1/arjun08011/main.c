#define F_CPU 16000000UL
#include <avr/io.h>
#include "lcd.h"
#include "delay_x.h"

int main() {
	lcd_init(LCD_DISP_ON | LCD_DISP_ON_CURSOR_BLINK);
	while(1) {
		lcd_clrscr();
		_delay_ms(100);
		lcd_home();
		lcd_puts("Arjun");
		_delay_ms(100);
	}
}
