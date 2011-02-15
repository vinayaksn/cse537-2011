//Reference: http://homepage.hispeed.ch/peterfleury/group__pfleury__ic2master.html
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
   int val_x;
   int vol_x;
   char value[10];
   char voltage[10];
   char * value1;
   char * voltage1;
   //lcd_init(LCD_DISP_ON);   
   DDRD = 3;
   PORTD = 1;
   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
   
   //ADMUX |= (1 << ADLAR);
   //ADMUX |= 1;
   //ADCSRA |= (1 << ADFR); 
   
   ADCSRA = ADCSRA | (1<<ADEN); // Enable ADC 
   
             
	       ADCSRA = ADCSRA | (1<<ADSC); // Start A2D Conversions 
		   
           
		   val_x=ADCL;
		   val_x = val_x | (ADCH<<8);
		   itoa(val_x,value,10);
		   value1 = value;             
           vol_x = val_x * 5;
           itoa(vol_x,voltage,10);
		   voltage1 = voltage;
		   return val_x;
		         
           

            
}

int main(){


unsigned int temp, ret, read;

char buf[10];
lcd_init(LCD_DISP_ON);
lcd_clrscr();




i2c_init();
		

    while(1)
	{
    ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
    if ( ret ) 
	{
        /* failed to issue start condition, possibly no device found */
        i2c_stop();
        // ret=0 -> Ok, ret=1 -> no ACK 
    }
	
	else 
	{
        /* issuing start condition ok, device accessible */
                              // write address = 5
       
	   
        i2c_write(0x00);
		unsigned int read_8;
		for(int i = 0; i < 30; i++)
		{
		   
		   int read_from_adc = readADC();
		   read_8 = read_from_adc/4;
		   //char read_char[10];
		   //read_from_adc=i;
		   /*itoa(read_from_adc,read_char,10);
		   const * value1 = read_char; 
		   lcd_clrscr();
		   _delay_ms(100); 
		   lcd_puts("Value: "); 
		   lcd_puts(value1); 

		   //itoa(read_from_adc,read_char,10);
		   
		   ret = read_char[0];*/

           i2c_write(read_8); 
		   _delay_ms(100);
		   
        }

           i2c_stop();
		   int count = 0x00;
           /*i2c_start_wait(Dev24C08+I2C_WRITE);     // set device address and write mode
           i2c_write(0x00);                        // write address = 5
           i2c_rep_start(Dev24C08+I2C_READ);*/       // set device address and read mode
		   int total = 0;
		   i2c_start_wait(Dev24C08+I2C_WRITE);
		   i2c_write(0x00); 
		   i2c_rep_start(Dev24C08+I2C_READ);

		for(int i = 0; i < 29; i++)
		{
		   
           read = i2c_readAck(); 
		   read = read*4;
		   total+=read;
           /*sprintf( buf, "read hua : %d", read );
		   lcd_clrscr();
           _delay_ms(100);		   
		   lcd_puts( buf );	 
		   _delay_ms(100);*/
		   count++;
        }

        read = i2c_readNak(); 
		i2c_stop();
		read = read*4;
		total+=read;

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
