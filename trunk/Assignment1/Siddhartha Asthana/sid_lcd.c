#define F_CPU 16000000UL
#include <avr/io.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"

int main(void){

lcd_init(0x0c);
_delay_ms(1000);
lcd_clrscr();
while(1){
_delay_ms(1000);
lcd_clrscr();
lcd_puts("Siddhartha \n Asthana");


}
return 0;
}
