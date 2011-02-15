#define F_CPU 16000000UL
#define Dev24C08 0xA0

#include<avr/io.h>

#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include "i2cmaster.h"
#include "twimaster.c";

int adc_val()
{
   int val1;
   int volt;
   char value[10];
   char voltage[10];
   char * val_x;
   char * val_y;
   
   
   
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
   
   
   ADCSRA = ADCSRA | (1<<ADEN); // Enable ADC 
   
             
	       ADCSRA = ADCSRA | (1<<ADSC); // Start A2D Conversions 
		   
           
		   val1=ADCL;
		   val1 = val1 | (ADCH<<8);
		   itoa(val1,value,10);
		   val_x = value;             
           volt = val1 * 5;
           itoa(volt,voltage,10);
		   val_y = voltage;
		   return val1;
		         
           

            
}

int main(){


unsigned int temp, ret, vall;

char buf[10];
lcd_init(LCD_DISP_ON);
lcd_clrscr();




i2c_init();
		

    while(1)

	{
    ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
    if ( ret ) 
	{
   
        i2c_stop();
   
    }
	
	else 
	{
         
	   
        i2c_write(0x00);
		unsigned int input1;
		for(int i = 0; i < 30; i++)
		{
		   
		   int inp1 = adc_val();
		   input1 = inp1/4;
		   
           i2c_write(input1); 
		   _delay_ms(100);
		   
        }

           i2c_stop();
		   int addd = 0x00;
           
		   int total = 0;
		   i2c_start_wait(Dev24C08+I2C_WRITE);
		   i2c_write(0x00); 
		   i2c_rep_start(Dev24C08+I2C_READ);

		for(int i = 0; i < 29; i++)
		{
		   
           vall = i2c_readAck(); 
		   vall = vall*4;
		   total=total+vall;
           /*sprintf( buf, "read hua : %d", read );
		   lcd_clrscr();
           _delay_ms(100);		   
		   lcd_puts( buf );	 
		   _delay_ms(100);*/
		   addd++;
        }

        vall = i2c_readNak(); 
		i2c_stop();
		vall = vall*4;
		total+=vall;

		int avg = total/30;
        lcd_clrscr();
        //_delay_ms(1000);	
        sprintf( buf, "Average : %d", avg );
        lcd_puts( buf );	 
		//_delay_ms(1000);

	                       
                                    // set stop conditon = release bus 
        
    
	 }


}


}
