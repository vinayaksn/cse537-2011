#define F_CPU 16000000UL

#include <avr/io.h>
#include "delay_x.h"
#include "lcd.h"
#include "lcd.c"

int main (void)
{   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz
   ADCSRB&=~((1<<ADTS0)|(1<<ADTS1)|(1<<ADTS2));
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC

   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode

//ADMUX |= (ADLAR)
ADCSRA |= (1<<ADEN);
ADCSRA |= (1<<ADSC);
char buf[15],str[19];
unsigned int adc;
double temperature;

while(1){
adc=ADC;
temperature= adc * 0.5;
sprintf( buf, "READING: %03d\t%d\r\n", adc, (int)temperature);
_delay_ms(10);
//str= "Reading: " + buf;
lcd_puts(buf);


}
return 0;
}
