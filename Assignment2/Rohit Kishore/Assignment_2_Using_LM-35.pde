/*
  This code works on the Arduino platform
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int pin = 1; // analog pin
int tempc = 0; // temperature variable

void setup()
{
  
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);  // for sensor out
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);  //for sensor in
  
  
  lcd.begin(16, 2);
  lcd.print("Current Temp :- ");
  lcd.setCursor(6,1);
  lcd.print("* C");
}

void loop()
{

tempc = ( 5.0 * analogRead(pin) * 100.0) / 1024.0;
lcd.setCursor(0,1);
lcd.print(tempc);
delay(1500); // delay before loop
tempc = 0;
}
