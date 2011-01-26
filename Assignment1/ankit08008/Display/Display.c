#define F_CPU 16000000UL
#include<avr/io.h>
#include"delay_x.h"
#include"lcd.h"
#include"lcd.c"
int main()
{
  lcd_init(LCD_DISP_ON);
  _delay_ms(1000);
  lcd_clrscr();
  
  
  _delay_ms(1000);

 while(1)
 {
   lcd_clrscr();
   _delay_ms(1000);
   lcd_puts("Ankit Kadam");
   _delay_ms(1000);
 }

}
