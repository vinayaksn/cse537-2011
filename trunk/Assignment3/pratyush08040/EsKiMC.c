//Acknowledgement vibhas (2008057)
#define F_CPU 16000000UL
#define Dev24C08 0xA0


#include<avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "delay_x.h"
#include "i2cmaster.h"


int readADC()
{
   int a1;
   char value[10], voltage[10];
   char * value1;
   char * voltage1;   
              
   a1=ADCL;
   a1 = a1 | (ADCH<<8);
  itoa(a1,value,10);
  return a1;
		        
}


int main()
{
unsigned int temp, ret, read;
char buf[10];
lcd_init(LCD_DISP_ON);
lcd_clrscr();
_delay_ms(1000);

i2c_init();
lcd_clrscr();
_delay_ms(100);	 	 
_delay_ms(1000);

lcd_clrscr();
 _delay_ms(1000);	 
 lcd_puts("2");	 
_delay_ms(1000);






    ret = i2c_start(Dev24C08+I2C_WRITE);     
    if ( ret ) 
	{ 
	    i2c_stop(); 
    }
	
	else 
	{
        i2c_write(0x00);
		unsigned int read_8;
		for(int i = 0; i < 30; i++)
		{
		  
		  int read_from_adc = readADC();
		  read_8 = read_from_adc/4;
		  char read_char[10];
		  itoa(read_from_adc,read_char,10);
		  const * value1 = read_char; 
		  lcd_clrscr();
		  _delay_ms(100); 
		  lcd_puts(value1); 
		  
		  ret = read_char[0];
          i2c_write(read_8); 
		  _delay_ms(100);
		  
        }


          i2c_stop();
		  int count = 0x00;
		  int total = 0;


		for(int i = 0; i < 30; i++)
		{
		  i2c_start_wait(Dev24C08+I2C_WRITE);
		  i2c_write(count); 
		  i2c_rep_start(Dev24C08+I2C_READ);
          read = i2c_readNak(); 
		  read = read*4;
		  total+=read;
		  lcd_clrscr();
           _delay_ms(100);		  
		  lcd_puts( buf );	 
		  _delay_ms(100);
		  count++;
        }


		int avg = total/30;
        lcd_clrscr();
         _delay_ms(1000);	
        sprintf( buf, "Average : %d", avg );
        lcd_puts( buf );	 
		  _delay_ms(1000);

        i2c_stop();                         

   	}
	}
