/*
Made for use with arduino libraries
Analog-3 pin is connected to Vout of LM35
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 4, 5, 6, 7);

void setup() {
}

void loop() {
  int temp = (analogRead(3) * 100.0 * 5.0 / 1024.0);
  lcd.setCursor(0,0);
  lcd.print(temp);
  delay(1000);
}
