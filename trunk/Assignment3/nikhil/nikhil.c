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

int count=0, avg=0, sum=0, i;
unsigned char temp, ret;

char buf[10];
lcd_init(LCD_DISP_ON);
lcd_clrscr();
_delay_ms(1000);



i2c_init();
		lcd_clrscr();
	  _delay_ms(100);	  
      lcd_puts("1");	  
	  _delay_ms(1000);

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescaler to 128 - 125KHz sample rate @ 16MHz
	ADCSRB &= ~(1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


	ADMUX |= (1 << REFS0); // Set ADC reference to AVCC

	//No MUX values needed to be changed to use ADC0

	ADCSRA |= (1 << ADATE);  // Set ADC to Free-Running Mode
	ADCSRA |= (1 << ADEN);  // Enable ADC

	ADCSRA |= (1 << ADIE);  // Enable ADC Interrupt
	//sei();   // Enable Global Interrupts

	ADCSRA |= (1 << ADSC);  // Start A2D Conversions


		ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode
        i2c_write(0x05);                       // write address = 5
        i2c_write('a');                       // ret=0 -> Ok, ret=1 -> no ACK 
        i2c_stop();                            // set stop conditon = release bus

        /* write ok, read value back from eeprom address 0x05, wait until 
           the device is no longer busy from the previous write operation */
        i2c_start_wait(Dev24C08+I2C_WRITE);     // set device address and write mode
        i2c_write(0x05);                        // write address = 5
        i2c_rep_start(Dev24C08+I2C_READ);       // set device address and read mode
        ret = i2c_readNak();                    // read one byte
        i2c_stop();
    
//	}

	sprintf( buf, "read : %c", 'a' );
	 
		lcd_clrscr();
	  _delay_ms(100);	  
      lcd_puts( buf );	  
	  _delay_ms(1000);

ret = i2c_start(Dev24C08+I2C_WRITE);       // set device address and write mode

while(1){
unsigned int vt;
count=0x00;
for(i=0; i<30; i++)
{

	unsigned int adc_value;
	adc_value=ADCL;
	adc_value|=(ADCH<<8);
	lcd_init(LCD_DISP_ON);
	_delay_ms(100);
	char value[8];
	float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
	float R=1000.0; 			// Fixed resistance in the voltage divider
	float logRt,Rt,T;
	int Vo = adc_value;
	Rt = R*( 1023.0 / (float)Vo - 1.0 );
	logRt = log(Rt);
	T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;   //SteinHart equation implementation
	itoa((int)T, value, 10);
	
        i2c_write(count);                       // write address = 5
        i2c_write(T);
		count++;
	}                       // ret=0 -> Ok, ret=1 -> no ACK 
        i2c_stop();   
		count=0x00;
		lcd_clrscr();
		_delay_ms(100);  
		sum=0;                       // set stop conditon = release bus
	for(i=0;i<30;i++)
	{
	//lcd_clrscr();
	//_delay_ms(100);
	
		
        /* write ok, read value back from eeprom address 0x05, wait until 
           the device is no longer busy from the previous write operation */
        i2c_start_wait(Dev24C08+I2C_WRITE);     // set device address and write mode
        i2c_write(count);                        // write address = 5
        i2c_rep_start(Dev24C08+I2C_READ);
		 
		//sprintf( buf, "Sum : %c", sum );      // set device address and read mode
        //sum+ = atoi(i2c_readNak());
		vt=i2c_readNak();
		sum  = sum + (int)vt;
		//sprintf( buf, "Value : %d",  i2c_readNak());
		//lcd_puts(buf);
		//_delay_ms(100);
		count++;
		
	}              
	
	
	sprintf( buf, "sum : %d", sum);
	lcd_puts(buf);
	_delay_s(1);
        i2c_stop();
    
	 

	}
}
