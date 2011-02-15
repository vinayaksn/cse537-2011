#define F_CPU 16000000UL
#define Dev24C08 0xA0

#include<avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include "lcd.c"
#include "delay_x.h"
#include "i2cmaster.h"
#include "twimaster.c"

int main(){


	unsigned int temp, ret;
    int i=0;
    char value[100];
    unsigned int x,high,low,aval,counter,read_eeprom;


	char buf[10];
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	_delay_ms(1000);

   ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 128 - 125KHz sample rate @ 16MHz 
   ADMUX |= (1 << REFS0); // Set ADC reference to AVCC 
   ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
   ADCSRA |= (1 << ADEN);  // Enable ADC 
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions 
   _delay_ms(100);     


	i2c_init();
    lcd_init(LCD_DISP_ON);   /* initialize display, cursor off */ 

	lcd_clrscr();
 	_delay_ms(100);  
    lcd_puts("1");  
 	_delay_ms(1000);

	  //ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
      //i2c_write(0x00);                       // write address = 5
      //i2c_write('1');                       // ret=0 -> Ok, ret=1 -> no ACK 
      //i2c_stop();                            // set stop conditon = release bus
      lcd_clrscr();



	 counter = 0x00;	
	 ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
     i2c_write(0x00);
	 
	
	 for(i=0; i<30;i++)
		{
	           low = ADCL;            //Make certain to read ADCL first, it locks the values
                high = ADCH;           //and ADCH releases them.

				int read_ADC=0;
                aval = (high << 8) | low;
	            //itoa((int)aval, value, 10);
                read_ADC=aval;
				x= read_ADC/4;
	  	  
			//i2c_write(counter);                       // write address = 5
      			i2c_write(x);                       // ret=0 -> Ok, ret=1 -> no ACK 
      			_delay_ms(100);
		}

	i2c_stop();                            // set stop conditon = release bus
      

		 _delay_ms(100);  
         lcd_puts("written in eeprom");  
         _delay_ms(1000);

    			int count = 0x00;
             	 unsigned int total = 0;

	  /* write ok, read value back from eeprom address 0x05, wait until 
         the device is no longer busy from the previous write operation */
        i2c_start_wait(Dev24C08+I2C_WRITE);     // set device address and write mode
		
		for(int i = 0; i < 30; i++)
		{
			i2c_write(count);                        // write address = 5
        	i2c_rep_start(Dev24C08+I2C_READ);       // set device address and read mode
        	read_eeprom = i2c_readNak();                    // read one byte
        
			read_eeprom=read_eeprom*2;
		
			//sprintf( buf, "read : %c", read_eeprom );
			total+=read_eeprom;
            sprintf( buf, "read: %d", read_eeprom );
 // 			lcd_clrscr();
 //          _delay_ms(100);   
 // 			lcd_puts( buf );  
 // 			_delay_ms(100);
  			count++;
		}

i2c_stop();

unsigned int average= total/30;

 lcd_clrscr();
           _delay_ms(1000);
        sprintf( buf, "Average : %d", average);
        lcd_puts( buf );  
  _delay_ms(1000);

/*i2c_write(0x05);
        i2c_write('a');*/                       
        i2c_stop();                        
    }
// }



