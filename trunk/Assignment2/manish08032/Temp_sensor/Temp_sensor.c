
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdlib.h>
#include<string.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"

char rslt[5];



uint16_t ReadADC()
   {
      //Start Single conversion

   ADCSRA|=(1<<ADSC);

   
   while(!(ADCSRA & (1<<ADIF)));//Wait for conversion to complete
		


   
   ADCSRA|=(1<<ADIF);//Clear ADIF by writing one to it
    
   return(ADCL);
 }





int main()
{
  uint16_t adc_value;
  
  uint8_t t;

	char tmp[6]="temp=";

   lcd_init(LCD_DISP_ON);
   _delay_ms(1000);
   lcd_puts("testing....");
      _delay_ms(1000);
   
	 lcd_clrscr();
      
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz      

   ADMUX |= (1 << REFS0); // set refrence voltage

   //ADMUX |= (1 << ADLAR); // left adjust ADC result.

   ADCSRA |= (1 << ADEN);  // Enable ADC 
   
  
       

  while(1)
   {
     strcpy(tmp,"Temp=");
	  

      adc_value= ReadADC();//Read ADC
      
      adc_value |= (ADCH<<8);
      t=adc_value/2;//Convert to degree Centrigrade

      //Print to display
     	 
	 lcd_puts("Sensing..");
      _delay_ms(1000);

	 lcd_clrscr();
             
   itoa(t,rslt,10);
    strcat(tmp,rslt);
      
   lcd_puts(tmp);
     _delay_ms(1000);
	 lcd_clrscr();
	 
   	  
   }
   
   return 0;
 }

   


 
  
