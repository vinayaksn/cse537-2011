#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay.h>
#include "lcd.c"
#include <stdio.h>

int main(){

char arr[1000];
uint8_t l,h;
uint16_t test;
double result,k=10;
ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

ADMUX|=(1<<REFS0);
//ADMUX|=(1<<ADLAR);

  // Set ADC to Free-Running Mode
   ADCSRA|=(1<<ADATE);

   ADCSRB|=(0<<ADTS0)|(0<<ADTS1)|(0<<ADTS2);
   
   ADCSRA |= (1 << ADEN);  // Enable ADC
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions

lcd_init(LCD_DISP_ON);
    lcd_clrscr(); 
_delay_ms(50);	
 //int test=0;	            
while (1)                         
{
l=ADCL;
h=ADCH;
test=(h<<8)|l;

//result=(test*5)/1024;
//result*=k;

sprintf(arr,"ADC=%d.",test);
lcd_puts(arr);    

_delay_ms(500);
lcd_clrscr(); 
_delay_ms(50);                    

}

return 0;
}
