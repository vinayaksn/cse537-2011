//Prateek Gaur..... 
// Currently just works for analog to digital conversion
// Not specific for thermistor

#define F_CPU 16000000UL //Frequency of CPU - 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>


int main (void)
{
	DDRD = 1; //For powering the thermistor
	PORTD = 1;

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz
	ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC

	//No MUX values needed to be changed to use ADC0

	ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
	ADCSRA |= (1 << ADEN);  // Enable ADC

	ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt
	sei();   // Enable Global Interrupts

	ADCSRA |= (1 << ADSC);  // Start A2D Conversions

	lcd_init(LCD_DISP_ON	);
	for(;;)  // Loop Forever
	{
	}
}


ISR(ADC_vect)
{
	unsigned int adc_value;
	char value[100];

	adc_value=ADCL;
	adc_value|=(ADCH<<8);

	lcd_init(LCD_DISP_ON);
	_delay_ms(3000);
     itoa((int)adc_value, value, 10);
	lcd_puts(value);
	_delay_ms(3000);
}

