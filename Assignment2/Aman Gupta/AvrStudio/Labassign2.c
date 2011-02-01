#define F_CPU 16000000UL
#include <avr/io.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include <string.h>

int main (void)
{

	int x=0;


	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= (0 << MUX1) | (0 << MUX0)|(0 << MUX2);
	
	ADMUX |= (1 << REFS0);
	ADMUX |= (0 << ADLAR);
	
	ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);

	lcd_init(LCD_DISP_ON);                  		//Initial ADC
	_delay_ms(1000);
	lcd_clrscr();
	_delay_ms(1000);

  	while (1)
	{

   		lcd_clrscr();
		_delay_ms(1000);
		x=ADCL;
		x|=(ADCH<<8);
		
		//x=ADC;
		
		char str[10];
		sprintf( str, "%d", x );
	
    	_delay_ms(1000);
		lcd_puts(str);
		_delay_ms(1000);
	  
	}
} 
