#include <avr/io.h> 
#include <string.h>
#include <stdio.h>
#include "delay_x.h"
#define F_CPU 16000000UL
#include <stdlib.h>
#include "uart.h"
#include "uart.c"

#define BAUD 9600UL
#define UBRRVAL (F_CPU/(BAUD*16)-1)
#define USE_SLEEP 1

int prev=0;
int prev1=0;


//#include <avr/pgmspace.h>
// char* to_string(uint8_t num);


int main (void) 
{

uart_init();
    char value[100];
    char temp[100]; 

	DDRD = 0xC4; //For powering the smoke sensor
    PORTD = 0xC0;

   unsigned int high,low,aval;


     _delay_ms(100);     

   // initializing registers for ADC
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 


   	ADMUX |=0x01;
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
//	ADMUX |= (1 << ADLAR);

   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
   ADCSRA |= (1 << ADEN);  // Enable ADC 
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
   _delay_ms(100);     


   for(;;)  // Loop Forever 
   { 

     if(ADMUX==65)
  		{
          _delay_ms(1000);
          low = ADCL;            //Make certain to read ADCL first, it locks the values
          high = ADCH;           //and ADCH releases them.
          aval = (high << 8) | low;
		 // aval= ADC;
          itoa((int)aval, value, 10);
			
		if((int)aval-prev>20)
		{
		uart_puts("buzz smoke");
		uart_puts("\r\n");


			PORTD = 0xC4;
			_delay_ms(1000);
			PORTD =0xC0;
		}
                                
 		uart_puts("ppm =");
		uart_puts(value);
		uart_puts("\r\n");

		prev=(int)aval;
	}

	else if(ADMUX==64)
	{
              _delay_ms(1000);
         
               low = ADCL;            //Make certain to read ADCL first, it locks the values
                high = ADCH;           //and ADCH releases them.
              aval = (high << 8) | low;
        	itoa((int)aval, value, 10);
             _delay_ms(1000);
             int x= aval/2;
             itoa(x, temp, 10);
 		uart_puts("temp =");
		uart_puts(temp);
		uart_puts("\r\n");
		
		if(x>50)
		{
			uart_puts("buzz temp");
			uart_puts("\r\n");

			PORTD = 0xC4;
			_delay_ms(1000);
			PORTD =0xC0;
		}

		prev1= x;
}
  
    if(ADMUX==64)
		ADMUX|=0x01;

	else
		ADMUX=0;

	ADMUX|=(1<<REFS0);
//		ADMUX |= (1 << ADLAR);
 
} 

return 0;
} 
