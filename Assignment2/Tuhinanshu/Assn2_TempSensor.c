#define F_CPU 16000000UL
#include <avr/io.h>
#include <lcd.h>
#include <lcd.c>
#include <stdlib.h>
#include <delay_x.h>

void InitADC()
{
ADCSRA |=(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); //Prescalar div factor =128
ADMUX=(1<<REFS0);                         // For Aref=AVcc;
ADCSRA |= (1 << ADEN);  // Enable ADC 
}

uint16_t ReadADC()
{

   //Start Single conversion
   ADCSRA|=(1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it


   ADCSRA|=(1<<ADIF);

   return(ADC);
}

int main()
{
   uint16_t adc_result;
   uint16_t temp;
   char tempstr[4];

   //Initialize LCD
   lcd_init(LCD_DISP_ON);
   lcd_clrscr();
   //Initialize ADC
   InitADC();


   

   while(1)
   {
      lcd_puts("Current");
      lcd_gotoxy(0,1);
      lcd_puts("Temp=");
      adc_result=ReadADC();           // Read Analog value
      temp=adc_result*5*100/1024;   // Converting temp to degree celsius
      itoa(temp,tempstr,10);
      lcd_puts(tempstr);          //Print the value in 4th column second line
      _delay_s(5);
      lcd_clrscr();
      lcd_puts("Lets Measure");
	  lcd_gotoxy(0,1);
      lcd_puts("Again");
      _delay_s(2);
      lcd_clrscr();
   }
   return 0;
   }
