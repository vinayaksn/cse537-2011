#include <LiquidCrystal.h>

int pin = 0; 
int temp = 0;
int samples[10];

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//int i;

void setup()
{
  
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  
  lcd.begin(16,2);
  lcd.print("Temperature is : ");
  lcd.setCursor(6,1);
}

void loop()
{
 int i;
 for(i=0;i<=9;i++)
  { 
 
    samples[i] = ( 5.0 * analogRead(pin) * 100.0) / 1024.0;
    temp = temp + samples[i];
    delay(100);

  }

  temp = temp/10.0;
  lcd.setCursor(0,1);
  lcd.print(temp);
  delay(1000);
  temp=0;
}
