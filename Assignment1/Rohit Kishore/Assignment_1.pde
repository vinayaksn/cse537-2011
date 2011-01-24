/*
  This code works on the Arduino platform
 */

#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW); //make an additional ground for backlight purposes
  delay(200);
  lcd.begin(16, 2);
/*
  lcd.print("Hi!! My name is");
  
  lcd.setCursor(0, 1);
*/
  lcd.print("Rohit Kishore");
}

void loop() {
  
}

