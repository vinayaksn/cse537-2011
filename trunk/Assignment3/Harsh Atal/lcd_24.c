#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay.h>
#include "lcd.c"
#include <stdio.h>
 
#include "twimaster.c"

 #define Dev24C02 0xA2  

int main()
{
unsigned char ret;
int tag=1,dummy=1,average=0,i;
char arr[10];
uint8_t l,h;
uint16_t test;

lcd_init(LCD_DISP_ON);
    lcd_clrscr(); 
_delay_ms(50);	
	           lcd_puts("starting...");  _delay_ms(50);
ADCSRA|=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

ADMUX|=(1<<REFS0);
//ADMUX|=(1<<ADLAR);

 
   ADCSRA|=(1<<ADATE);
 // Set ADC to Free-Running Mode
   ADCSRB|=(0<<ADTS0)|(0<<ADTS1)|(0<<ADTS2);
   
   ADCSRA |= (1 << ADEN);  // Enable ADC
   ADCSRA |= (1 << ADSC);  // Start A2D Conv


i2c_init();  


for (i=0;i<30;i++){
 _delay_ms(100);
l=ADCL;
h=ADCH;
test=(h<<8)|l;
test=test;
i2c_start_wait(Dev24C02+I2C_WRITE);     // set device address and write mode
    
	 i2c_write(i);                        // write address = 5
     i2c_write(test);                        // write value 0x75 to EEPROM
	 i2c_stop();                             // set stop conditon = release bus

}

i2c_start_wait(Dev24C02+I2C_WRITE);     // set device address and write mode

     i2c_write(0);                        // write address = 5
     i2c_rep_start(Dev24C02+I2C_READ);       // set device address and read mode

for (i=0;i<30;i++){


     ret = i2c_readAck();

	 sprintf(arr,"byte read=%d.",(int)ret);

lcd_puts(arr);  _delay_ms(200);     
lcd_clrscr(); 
_delay_ms(50);               // read one byte from EEPROM
     average=average+ret;
	 }
average=average/30;


		lcd_clrscr(); _delay_ms(500);                    

//lcd_write(49,1);  
sprintf(arr,"val=%d.",average);

lcd_puts(arr);  _delay_ms(500);

//i2c_stop();
//}
//dummy=dummy-1;
}
