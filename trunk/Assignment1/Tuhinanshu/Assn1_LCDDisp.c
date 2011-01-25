/* Author: Tuhinanshu
   Roll No. :2008056
   Assignment-1
   External Libraries Used: lcd.c, lcd.h from http://www.jump.to/fleury/
   Acknowledgements : - 
   Thanks to Mr. Abhishek(TA), for explaining how to setup the lcd and how to connect it to the atmega328p board. 
   The link provided by him was of great help - http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=81823.
   It helped in understanding the various lcd functions.
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <delay_x.h>
#include <lcd.h>
#include <lcd.c>

int main(void)
{
 lcd_init(LCD_DISP_ON);              #to put on the LCD 
 lcd_clrscr();                       #to clear the LCD Screen
 lcd_puts("Tuhinanshu");             #to put the string inside quotes on the LCD Screen
 while(1)
 {
  lcd_command(LCD_MOVE_DISP_LEFT);   #to shift the display left
  _delay_ms(500);                    #to give a delay of half second between each left shift
 }
}
