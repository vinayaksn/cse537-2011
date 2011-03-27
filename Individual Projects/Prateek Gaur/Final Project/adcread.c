//Prateek Gaur 2008039


#define F_CPU 16000000UL
#include<avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"


int main(){

unsigned int adc_value,k;

	char str[100];
	
    
lcd_init(LCD_DISP_ON);           //setting the led
lcd_clrscr();
_delay_ms(1000);


      


	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz
	ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC

	//No MUX values needed to be changed to use ADC0

	ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
	ADCSRA |= (1 << ADEN);  // Enable ADC

	         

	ADCSRA |= (1 << ADSC);  // Start A2D Conversions
	
   DDRD|=((1<< PORTD0)|(1<< PORTD1));
   DDRB|=(1<< PORTB1);
  
   
   PORTD|=1 << PORTD1;
   PORTD&= ~( 1 << PORTD0);
   //DDRD|=(1<<PORTD6);
   TCCR1A = 0b10000001; // Fast PWM 8 Bit
  TCCR1B = 0b00000001; // No Prescaler
  TCNT1 = 0;           // Reset TCNT0
  
 // OCR1A=255;
   

		
	while(1)
	{
     
	    adc_value=ADCL;
		adc_value|=(ADCH<<8);
		
		k=adc_value;              //dividing by 2^2 so as to fit in 8 bit address
	  		
		_delay_ms(100);
		if(k >=500)
		{
		    OCR1A=255;
		}
		else if(k>=400 && k <500)
		{
		    OCR1A=200;
		}
		else if(k <400 && k >=200 )
		{
		    OCR1A=130;
		}
		else if(k<200 && k >=100)
		{
		    OCR1A=80;
		}
		else 
		{
		    OCR1A=0;
		}
		 lcd_clrscr();		 
	    _delay_ms(1000);	
		sprintf(str, "ADC: %d",k);  
        lcd_puts(str);	  
	    _delay_ms(1000);
       

}
}
