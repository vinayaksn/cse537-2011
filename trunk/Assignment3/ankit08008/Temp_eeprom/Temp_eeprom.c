#define F_CPU 16000000UL
#include<avr/io.h>
#include"delay_x.h"
#include <stdlib.h>
#include<string.h>
#include"lcd.h"
#include"lcd.c"
#include "i2cmaster.h"
#include "twimaster.c"
#define Dev24C02  0xA2      // device address of EEPROM 24C02, see datasheet
int main()
{
  uint16_t value;
  char str[50];
  uint8_t ret;
  lcd_init(LCD_DISP_ON);
  
  _delay_ms(100);

  ADCSRA|= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //set prescalar
   ADMUX|= (1 << REFS0); // set reference to avcc
  ADCSRA|= (1 << ADEN); //enable ADC
  ADCSRA|=(1<<ADSC); //Stard A2D conversion
 
 _delay_ms(1000);
  lcd_clrscr();
  i2c_init();   
	 /*    lcd_clrscr();                      // initialize I2C library
     _delay_ms(100);
	 lcd_puts("Initialized I2C Lib");
  i2c_stop();*/
 while(1)
 {
   
   _delay_ms(100);
   lcd_clrscr();
   // i2c_init(); 
	 lcd_clrscr();                      // initialize I2C library
     _delay_ms(100);
	 lcd_puts("Initialized I2C Lib");

   char tmp[100];
  
 for(int i=0;i<30;i++)
 {  
 ADCSRA|=(1<<ADSC); // start conversion

 while(!(ADCSRA & (1<<ADIF)));// Conversion completion

  ADCSRA|=(1<<ADIF);//Clear ADIF by writing one to it

   value = ADCL; //take ADCL value
   value|= (ADCH<<8); //left shift ADCH & OR with val
   uint8_t temp = value/2;
   strcpy(tmp,"Temp=");
   itoa(temp,str,10);
   strcat(tmp,str);
   lcd_clrscr();
  lcd_puts(tmp);
    _delay_ms(100);
   //start writing
   i2c_start_wait(Dev24C02+I2C_WRITE);     // set device address and write mode
     i2c_write(i);                        // write address = i
     i2c_write(temp);                        // write value 0x75 to EEPROM
     i2c_stop();    
                         // set stop conditon = release bus
						 
}
  lcd_clrscr();
   
  lcd_puts("Writing complete");
  _delay_ms(100);
   //_delay_ms(100);
       // read previously written value back from EEPROM address 5 
     i2c_start_wait(Dev24C02+I2C_WRITE);     // set device address and write mode

     i2c_write(0x00);                        // write address = 5
     i2c_rep_start(Dev24C02+I2C_READ);       // set device address and read mode
     lcd_clrscr();
    _delay_ms(100);
     lcd_puts("Average = ");

	 int average=0;

     for(int i=0;i<30;i++)
	 {
	  ret= i2c_readAck();
	  average+=ret;
	 }

	 average=average/30;

	 char str[10];
	 lcd_gotoxy(0,1);
	  itoa(average,str,10);
	   _delay_ms(1000);
	   
	  lcd_puts(str);
	   _delay_ms(1000);
      i2c_readNak();                    // read one byte from EEPROM
     i2c_stop();



 }

}
