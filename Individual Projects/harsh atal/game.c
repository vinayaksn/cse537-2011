#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay.h>
#include "lcd.c"
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void set_led(int);
unsigned int get_random(int);
int button_event(void);
int queue[5],q_count=0,flag=0;

int main(){
char string[30],str_num[12],status[10];
int temp,counter,t_num,time_left=0,time_out_by_ten;
unsigned int time_out,inv_no,temp2,result=0;
int random_no=1,timer,flag=0,x;

uint8_t coord_x,coord_y;

srand(7);
lcd_init(LCD_DISP_ON);
    lcd_clrscr();  _delay_ms(50);
		
lcd_puts("welcome!!\n!!!!!!");    
_delay_ms(1000);
DDRC=0b000000;
PORTC=0b111111;
DDRB=0xff;
while(flag!=2){
// led
q_count=0;
	for(counter=0;counter<4;counter++)
	{
	random_no=get_random(random_no);
	queue[q_count++]=random_no;
	set_led(random_no);
	lcd_clrscr();  _delay_ms(5);
	sprintf(string,"Look at the led");
	lcd_puts(string);
	_delay_ms(700);
	PORTB=0;
	_delay_ms(300);
		//lcd_clrscr();  _delay_ms(5);
	}
 x=button_event();
if (x==1)
{
//PORTB=0;
PORTB=0x0;
_delay_ms(100);

lcd_clrscr();  _delay_ms(5);
sprintf(string,"Press 1 for trying again\n 2 to quit");
	lcd_puts(string);
	_delay_ms(1000);
	while(1){
		if (PINC==55){
		flag=0;
			break;}
		else if(PINC==59){
		lcd_gotoxy(0,0);
			sprintf(string,"byeee!!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!!");
		lcd_puts(string);
		_delay_ms(100);
		flag=2;
			break;
			}
		}
	}
}

return 0;
}


void set_led(int random){
int led_no=0;
if (random==1)
led_no=8;
else if(random==2)
	led_no=4;
	else if(random==3)
		led_no=2;
		else if(random==4)
			led_no=1;

PORTB=led_no;
}

unsigned int get_random(int prev){
int num=1;

//do
num=rand()%4 +1;
//while(num==prev);

return num;
}


int button_event(){
char string[10],t_str[12],str_time[10];
int button_press,num,count,timer=1000;

	lcd_clrscr();  _delay_ms(1);

button_press=PINC;
q_count=0;

while(q_count<4){
//button_press=PINC;
timer=timer-1;
if (timer<0)
	{
	lcd_gotoxy(0,0);
	sprintf(string," time out\ntry again    ");
	lcd_puts(string);
	_delay_ms(1000);
	//lcd_clrscr();  _delay_ms(5);
	//flag=1;
	return 1;
		}
switch(PINC){
	case 62: num=4;
			while(PINC!=63);
			break;
	case 61: num=3;while(PINC!=63);
			break;
	case 59: num=2;while(PINC!=63);
			break;
	case 55: num=1;while(PINC!=63);
			break;
	default : num=0;
			break;
	}

if (queue[q_count]==num){
sprintf(string,"%d",num);
strcat(t_str,string);

//t_str[q_count]=string[0];
lcd_gotoxy(q_count,0);
lcd_puts(string);
_delay_ms(70);
//lcd_clrscr();  _delay_ms(5);
q_count++;
}
	if(timer%10==0){
	lcd_gotoxy(0,1);
	sprintf(str_time,"Time Left=%d  ",timer/100);
	lcd_puts(str_time);
	
	_delay_ms(70);
	//lcd_clrscr();  _delay_ms(5);
		}
	
	}
//lcd_clrscr();  _delay_ms(5);
	_delay_ms(1000);
	lcd_gotoxy(0,0);
	sprintf(str_time,"win!!\n!!!!!!!!!!!");
	lcd_puts(str_time);
	
	_delay_ms(1500);

return 0;
}
