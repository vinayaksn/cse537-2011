#include <LiquidCrystal.h>
#define lm35_vout_in 0  //define pin for analog input
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



void setup() {
  // set up the LCD's number of columns and rows: 
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(13,LOW);   
  digitalWrite(8,LOW);   // Ground pin fot lm35
  digitalWrite(9,HIGH);  // Power pin for lm35
  lcd.begin(16, 2);
}

void loop() {
  lcd.clear();
  float temp_out;
  temp_out=(( 5.0 * analogRead(lm35_vout_in) * 100.0) / 1024.0);
  lcd.print(temp_out);
  delay(1000);
}

