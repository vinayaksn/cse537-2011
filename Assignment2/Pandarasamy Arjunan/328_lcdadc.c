/*
 *  328_lcdadc.c
 *
 *  Introducion to Embedded Systems - CSE537, Monsoon 2011
 * 
 *  Assignment 2 : Sensing temprature and display the temparature on LCD screen
 *
 *  Controller        : ATmega328P
 *  LCD Display       : JHD162A
 *  Temprature Sensor : LM35
 *
 *  Libraries    : LCD interface library(lcd.h,lch.c) from Peter Fleury(http://jump.to/fleury)
 *                 Accurate delay(delay_x.h) from Hans-Juergen Heinrichs
 *  
 *  References   : http://www.facstaff.bucknell.edu/mastascu/elessonshtml/Sensors/TempLM35.html
 *                 http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=56429
 * 
 */

#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"

int main()
{
   unsigned int adc;
   char buf[10];
   double temprature;

   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz   
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC

   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
   ADCSRA |= (1 << ADEN);  // Enable ADC
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions

   lcd_init(LCD_DISP_ON);
   _delay_ms(100);

   while(1)
   {
		lcd_clrscr();
		_delay_ms(1000);

		adc = ADCL;
		adc |= (ADCH<<8);		
		temprature = adc * 0.48828125;   // calibaration factor - ref[1]

		sprintf( buf, "%d %d", adc, (int)temprature);
        lcd_puts( buf );
	    _delay_ms(1000);
   }

   return 0;
}


