#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
//#include "lcd.h"
#include "lcd.c"
int main(void)
{
lcd_init(LCD_DISP_ON);
    lcd_clrscr(); 
//_delay_ms(50);	
	            /* initialize display, cursor off */
while (1)                         /* loop forever */
{


lcd_clrscr(); 
_delay_ms(500);                    /* clear the screen*/

lcd_puts("harsh");  
//lcd_puts("testjhgcgcncn program");           /* displays the string on lcd*/
_delay_ms(500);

}
}
