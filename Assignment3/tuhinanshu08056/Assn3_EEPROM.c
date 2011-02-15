/* Author: Tuhinanshu
   Roll No. :2008056
   Assignment-3
   External Libraries Used: lcd.c, lcd.h, i2cmaster.h,twimaster.c from http://www.jump.to/fleury/
   Acknowledgements : - 
   The link was of great help - http://homepage.hispeed.ch/peterfleury/group__pfleury__ic2master.html.
   It helped in understanding the various i2c functions.
*/



#define F_CPU 16000000UL
#include <avr/io.h>
#include <lcd.h>
#include <lcd.c>
#include <stdlib.h>
#include <delay_x.h>
#include "i2cmaster.h"
#include "twimaster.c"
#define Dev24C08  0xA2     // device address of EEPROM 24C08, 

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
   uint16_t adc_result,i;
   uint16_t sum,average;
   unsigned int temp;
   unsigned char ret;
   char tempstr[4];
   
   //char adc_char[4];


   //Initialize LCD
   lcd_init(LCD_DISP_ON);
   lcd_clrscr();
   
   //Initialize ADC
   InitADC();

    i2c_init();        //Initialize I2C
   

   while(1)
   {
      adc_result=0;
      lcd_puts("Sensing");
      lcd_gotoxy(0,1);
      lcd_puts("Temperature");
	  _delay_s(2);
	  ret = i2c_start(Dev24C08+I2C_WRITE);         //Setting up EEPROM for writing
	   
	   if (ret) {                                 
        /* failed to issue start condition, possibly no device found */
		lcd_clrscr();
		lcd_puts("No EEPROM found");
		_delay_s(2);
        i2c_stop();
      }

	  else{
	  lcd_clrscr();
	  lcd_puts("Storing Values");                 
	  _delay_s(2);
      i2c_write(0x00);

	  for(i=0;i<30;i++)
	  {
      adc_result=ReadADC();           // Read Analog value 
	  adc_result=adc_result/4;   
	  i2c_write(adc_result);           //write adc value to eeprom
	  _delay_ms(100);
	  }

	  i2c_stop();                     
	  lcd_clrscr();
	  lcd_puts("Sensing Complete");
	  _delay_s(2);

	  sum=0;
	  average=0;
      int counter=0x00;

       i2c_start_wait(Dev24C08+I2C_WRITE);         
       i2c_write(counter);                        // write address = counter
        i2c_rep_start(Dev24C08+I2C_READ);       // set device address and read mode

	  for(i=0;i<29;i++)
	  {
	  lcd_clrscr();
	  lcd_puts("Reading Values");
	    temp = i2c_readAck();                    // read one byte
		temp=temp*4;
		sum=sum+temp;
		//lcd_clrscr();
		//itoa(temp,adc_char,10);
        //lcd_puts(adc_char);
	   // _delay_ms(500);
	  }

	  temp = i2c_readNak();                      //reading last byte
       i2c_stop();
       temp=temp*4;
       sum+=temp;

	  lcd_clrscr();
	  lcd_puts("Calculating Avg");
	  _delay_s(2);

	  average=sum/30;                           //calculating average

	  itoa(average,tempstr,10);

	  lcd_clrscr();
	  lcd_puts("Average");
	  lcd_gotoxy(0,1);
	  lcd_puts("Reading=");
      lcd_puts(tempstr);

	  _delay_s(2);   
	  }       
      lcd_clrscr();
      
   }
   return 0;
   }
