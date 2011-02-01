#define F_CPU 16000000UL
#include<avr/io.h>
#include"delay_x.h"
#include <stdlib.h>
#include<string.h>
#include"lcd.h"
#include"lcd.c"
int main()
{
  uint16_t value;
  char str[50];

  lcd_init(LCD_DISP_ON);
  _delay_ms(1000);
  lcd_clrscr();
  
  
  _delay_ms(100);

  ADCSRA|= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //set prescalar
   ADMUX|= (1 << REFS0); // set reference to avcc
  ADCSRA|= (1 << ADEN); //enable ADC
  ADCSRA|=(1<<ADSC); //Stard A2D conversion

 while(1)
 {
   lcd_clrscr();
   _delay_ms(100);
   char tmp[100];
   strcpy(tmp,"Temp=");
   _delay_ms(100);

   value = ADCL; //take ADCL value
   value|= (ADCH<<8); //left shift ADCH & OR with val
   uint16_t temp = value/2;
   itoa(temp,str,10);
   strcat(tmp,str);
   lcd_puts(tmp);
   _delay_ms(1000);
 }

}
