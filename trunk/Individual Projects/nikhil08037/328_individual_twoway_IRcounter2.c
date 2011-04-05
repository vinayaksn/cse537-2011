#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> 
#include "delay_x.h"
#include "lcd.h"
#include "lcd.c"
#include <stdlib.h>

int prev=0;
int prev1=0;
int count=0;
int start=0;

int flag=0 	;		//for switching between the adc pins

int main()
{

	DDRD=1;
	PORTD=1;


 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to (111)128 - 125KHz sample rate @ 16MHz 
 ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
  // ADMUX |= (1 << ADLAR); // Left adjust ADC result to allow easy 8 bit reading 

   // No MUX values needed to be changed to use ADC0 

   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode 
   ADCSRA |= (1 << ADEN);  // Enable ADC 

   ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt 
  // sei();   // Enable Global Interrupts 

   ADCSRA |= (1 << ADSC);  // Start A2D Conversions 


  // lcd_init(LCD_DISP_ON);
   for(;;)
   {

unsigned int val;
val =ADCL;
val |=(ADCH << 8);
lcd_init(LCD_DISP_ON);
// for stein-hart equation from wikipedia and values found from http://web.cecs.pdx.edu/~gerry/class/EAS199B/howto/thermistorArduino/thermistorArduino.pdf
char result[10];
/*float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
float R = 1000.0; 			// Fixed resistance in the voltage divider
float logRt,Rt,T;
int Vo = val;
Rt = R*( 1023.0 / (float)Vo - 1.0 );
logRt = log(Rt);
T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;   //SteinHart equation implementation
*/
if(start==0)
{
 start=1;
 prev=(int)val;
 ADMUX |= (1 << REFS0);
 ADMUX|=0x05;
 val =ADCL;
 val |=(ADCH << 8); 
 prev1=(int )val;
 ADMUX=0x00;
 ADMUX |= (1 << REFS0);

 val =ADCL;
  val |=(ADCH << 8); 
 prev=(int )val;
}
if((int)val-prev>50 && ADMUX==64)
 {
  if(flag==0)
 {
	flag=1;
  }
if(flag==2)
{
flag=0;
count++;
 }

 }
if((int)val-prev1>50 && ADMUX==69)
 {

 if(flag==0)
 {
	flag=2;
  }
if(flag==1)
{
flag=0;
count--;
 }

}
if(ADMUX==64)
{
ADMUX|=0x05;
ADMUX |= (1 << REFS0);
 
prev=(int)val;

}
else
{
ADMUX=0x00;
ADMUX |= (1 << REFS0);
prev1=(int)val;

}


itoa((int)count, result, 10);



lcd_puts(result);
//_delay_s(1);
   }
}

