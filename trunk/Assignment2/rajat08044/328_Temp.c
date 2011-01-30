#define F_CPU 16000000UL //Frequency of CPU - 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include <stdio.h>
#include <stdlib.h>


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
	adc_value=ADCL;
	adc_value|=(ADCH<<8);
	lcd_init(LCD_DISP_ON	);
	_delay_ms(1000);
	char value[100];
	//The implementation of the steinhart equation has been taken from Rohit Kishore's code. I thank him for the same.
	float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
	float R = 1000.0; 			// Fixed resistance in the voltage divider
	float logRt,Rt,T;
	int Vo = adc_value;
	Rt = R*( 1023.0 / (float)Vo - 1.0 );
	logRt = log(Rt);
	T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;   //SteinHart equation implementation
	itoa((int)T, value, 10);
	lcd_puts(value);
	_delay_ms(1000);
}

