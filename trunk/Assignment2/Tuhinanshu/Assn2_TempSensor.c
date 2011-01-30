/* Author: Tuhinanshu
   Roll No. :2008056
   Assignment-2
   External Libraries Used: lcd.c, lcd.h from http://www.jump.to/fleury/
   Acknowledgements : - 
   These links were of great help - 
   http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=56429 &&
   http://extremeelectronics.co.in/avr-tutorials/using-the-analog-to-digital-converter/
   They helped in understanding the various ADC connections
*/


#define F_CPU 16000000UL
#include <avr/io.h>
#include <lcd.h>
#include <lcd.c>
#include <delay_x.h>
//#include <avr/interrupt.h>

void InitADC()
{
ADMUX=(1<<REFS0);                         // For Aref=AVcc;
ADCSRA |=(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); //Prescalar div factor =128
ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading 
//ADCSRA |= (1 << ADFR);  // Set ADC to Free-Running Mode 
ADCSRA |= (1 << ADEN);  // Enable ADC 
}

uint16_t ReadADC(uint8_t ch)
{
   ch=ch&0b00001000;
   ADMUX|=ch;

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

   DDRD = 1;
   PORTD = 1;
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
      adc_result=ReadADC(0);           // Read Analog value from channel-0
      temp=adc_result/2;                // Converting temp to degree celsius
	  lcd_gotoxy(4,1);
	  lcd_puts_p((char*)(temp)); //Print the value in 4th column second line
      _delay_s(5);
	  lcd_clrscr();
	  lcd_puts("Thankyou");
	  _delay_s(2);
	  lcd_clrscr();
   }
}
