#define F_CPU 16000000UL //Frequency of CPU - 16MHz
#define BAUD 9600
#define MYUBBR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.c"
#include "lcd.h"
#include "delay_x.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "USART328.h"
#include "USART328.c"


int main (void)
{
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz
	ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC

	//ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
	ADCSRA |= (1 << ADEN);  // Enable ADC


	lcd_init(LCD_DISP_ON);
	USART_init(MYUBBR);
	for(;;)  // Loop Forever
	{
		char buf[100];
		char buffer[80];
		unsigned int adc_value1, adc_value2;
		float RH;
		// Start A2D Conversions
		ADMUX |= (1 << MUX0);
		ADCSRA |= (1 << ADSC);
		adc_value1=ADCL;
		adc_value1|=(ADCH<<8);
		_delay_s(1);
		ADMUX = ADMUX-1;
		ADCSRA |= (1 << ADSC);
		adc_value2=ADCL;
		adc_value2|=(ADCH<<8);

		RH = ((adc_value2*0.49)-0.75)/3;
		if (RH>30)
		{
			DDRB = 1;
			PORTB = 1;
		}
		else
		{
			DDRB=0;
			PORTB=0;
		}
		sprintf(buffer, "%d,%d,\n", adc_value1,(int)RH);
		USART_String(buffer);
		sprintf(buf, "Humidity:\n%d %d", (int)adc_value1, (int)RH);
		lcd_puts(buf);
		_delay_s(1);
		lcd_clrscr();
	}
}
