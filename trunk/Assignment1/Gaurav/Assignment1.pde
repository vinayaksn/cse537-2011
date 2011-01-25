#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW); 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("\"Gaurav\"");
  }

void loop() {
  
}

