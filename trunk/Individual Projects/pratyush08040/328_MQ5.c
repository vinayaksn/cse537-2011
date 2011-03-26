#include <avr/io.h> 
#include <string.h>
#include <stdio.h>
#include "delay_x.h"
#define F_CPU 16000000UL

#include <stdlib.h>


int main (void) 
{

   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
       
   // No MUX values needed to be changed to use ADC0 
   ADCSRA |= (1 << ADEN);  // Enable ADC 
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions 


   DDRB=255;   
   unsigned int ppm,temp,low,high;
//------------------------------GAS SENSOR-------------------------------------     

   for(;;)  // Loop Forever 
   {

        _delay_ms(100);
		low = ADCL;            //Make certain to read ADCL first, it locks the values
        
        high = ADCH;           //and ADCH releases them.
        ppm = (high << 8) | low;

		if (ppm>=1023)
		{
		 
         PORTB = 11111111;
		}
      else
	  { PORTB = 00000000;}

   } 

  return 0;
} 
