
#define F_CPU 16000000UL

#include <avr/io.h>
#include<avr/interrupt.h>
#include<string.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"



int main()
{

	unsigned int adc;
	char buf[100];
	double temp;

   
    lcd_clrscr();
      
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz      
    	
   ADMUX |= (1 << REFS0); // set refrence voltage

  // ADMUX |= (0 << ADLAR); // left adjust ADC result.

   ADCSRA |= (1 << ADATE); 
   
   ADCSRA |= (1 << ADEN); // Enable ADC 
   ADCSRA|=(1<<ADSC);
  lcd_init(LCD_DISP_ON);
   _delay_ms(1000);
    
       

  while(1)
   {
    lcd_clrscr();
	_delay_ms(1000);
	lcd_puts("temp=");
	_delay_ms(1000);
	
	adc = ADCL; 
	adc |= (ADCH<<8); //left shift 
	
	temp = adc * 0.5;
	itoa((int)temp, buf,10);
	//sprintf(buf,"%d %f", adc, temp);   //convert to string
	lcd_puts(buf);
	_delay_ms(1000);
   	  
   }
   
   return 0;
 }

   


 
  

