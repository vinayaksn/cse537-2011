#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <inttypes.h>
#include <stdlib.h>
#include "delay_x.h"
#include "lcd.h"
#include <avr/signal.h> 
#include <stdio.h>
 
#define D5 851
#define E5 758
#define Fsh5 675
#define G5 637
#define A5 568
#define B5 506
#define C6 477
#define D6 425
#define DUR 40


void tone(uint16_t,uint8_t );

int main()
{
OSCCAL = 176;
DDRC = 0b00000001;
PORTC |= (1<<PC7);

 lcd_init(LCD_DISP_ON);

 while(1)
 {
 lcd_clrscr();
  _delay_ms(100);

 lcd_puts("press the button");
 _delay_ms(100);

 while(PINC & (1<<PC7))
 {
 ////nothing
 }

  lcd_clrscr();
  _delay_ms(100);


lcd_puts("happy");
tone(D5, DUR);
lcd_puts("birth");
tone(E5, DUR);
lcd_puts("day");
tone(D5, DUR);
lcd_puts("to");
tone(G5, DUR);
lcd_puts("you");
tone(Fsh5, 2*DUR);

 lcd_clrscr();
  _delay_ms(100);

lcd_puts("happy");
tone(D5, DUR);
lcd_puts("birth");
tone(E5, DUR);
lcd_puts("day");
tone(D5, DUR);
lcd_puts("to");
tone(A5, DUR);
lcd_puts("you");
tone(G5, DUR);

 lcd_clrscr();
  _delay_ms(100);

lcd_puts("happy");
tone(D5, DUR);
lcd_puts("birth");
tone(D6, DUR);
lcd_puts("day");
tone(B5, DUR);
lcd_puts("dear");
tone(G5, DUR);
lcd_puts("xyz");
tone(E5, DUR);

 lcd_clrscr();
  _delay_ms(100);


lcd_puts("happy");
tone(C6, DUR);
lcd_puts("birth");
tone(B5, DUR);
lcd_puts("day");
tone(G5, DUR);
lcd_puts("to");
tone(A5, DUR);
lcd_puts("you");
tone(G5, DUR);

 lcd_clrscr();
  _delay_ms(1000);
 }

return 0;
}


void tone(uint16_t period,uint8_t duration)
{

uint16_t d=100*duration;
uint16_t p=period/50;
uint16_t duty_cycle=d/p;

while(duty_cycle>0)
{
PORTC=1;
_delay_ms(period/2);
duty_cycle--;
PORTC=0;
_delay_ms(period/2);
duty_cycle--;
duty_cycle--;

}


}






