#include <SD.h>
#define SDCSSS 10
/*
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10 (SS)
*/


#include <LiquidCrystal.h>

// Requires the use of the "PS2Keyboard" library
#include <PS2Keyboard.h>

#define DATA_PIN 2
// white 2 1 data
// green 6 5 clock
// yellow 4 3 ground
// red 3 4 vcc
// Create a PS2Keyboard object called "keyboard". The PS2Keyboard library hard-codes
// the PS/2 'CLOCK' pin to Arduino's digital input 3, data pin 2
PS2Keyboard keyboard;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/**
 */
void setup()
{
  keyboard.begin(DATA_PIN);
  lcd.begin(16,2);
  // Set up the serial connection to report keypresses to the host
  Serial.begin(38400);
  Serial.println("Initialised PS/2 reader");
  
  if (!SD.begin(SDCSSS)) {
    Serial.println("SD initialization failed!");
    // return;
  } else {
    Serial.println("SD initialised");
  }
  
  delay(1000);
}

int readbuf(char buf[16]) {
  //lcd.clear();
  // lcd.setCursor(0,0);
  byte data, i = 0;
  
  Serial.print("reading buf\n");
  
  //while (!keyboard.available());  
  Serial.print("keyboard available\n");
  data = keyboard.read();
  while (data != '\n' && data != PS2_KC_ESC && i < 15) {
    Serial.print("\nread data: ");
    buf[i] = data;
    lcd.print((char)i);
    Serial.print((char)i);
    
    if (data == PC_KC_BKSP) {
      lcd.rightToLeft();
      lcd.print(" "); 
      lcd.leftToRight();
      lcd.print(" "); 
      lcd.rightToLeft();
      lcd.print(" "); 
      lcd.leftToRight(); 
      data[i] = 0;
      --i;
    }
    
    //if (++i == 16)
    //  lcd.setCursor(0, 1);
    
    while (!keyboard.available());  
    data = keyboard.read();
  }
  
  buf[i] = data;
  
  return i+1;
}

/**
 * Main program loop
 */
void loop()
{
  
  lcd.setCursor(0,0);
  lcd.print("Enter file name");
  lcd.setCursor(0,1);
  lcd.print("(8.3): ");
  
  char buf[32];
  byte i, data;
  keyboard.read();
  for (i = 0; i < 9; ++i) {
    while (!keyboard.available());
    
    data = keyboard.read();
    if (data == ' ')
      break;
    lcd.print(data);
      
    buf[i] = data;
  }
  
  buf[i] = 0;
  
  /*
  if (!SD.exists(buf)) {
    lcd.setCursor(0,0);
    lcd.print("File not found");
    lcd.setCursor(0,1);
    lcd.print(buf);
    return;
  }
  */
  
  File out = SD.open(buf, FILE_WRITE);
  
  if (!out) {
    Serial.print("Cannot open file:");
    Serial.print(buf);
    Serial.print(".\n");
  } else {
    Serial.print("Opened file: ");
    Serial.print(buf);
    Serial.print(".\n");
  }
  
  
  //lcd.setCursor(0,0);
  lcd.clear();
  i = 0;
  while (1) {
    
    byte n = readbuf(buf);
    out.write(buf, n);
    
    /*while (!keyboard.available());
    data = keyboard.read();
    if (data == PS2_KC_ESC)
      break;
      
    if (data == PS2_KC_ENTER)
      data = '\n';
      
    Serial.print((char)data);
    lcd.print((char)data);
    out.write(&data, 1);
    if (++i == 15) {
      lcd.clear();
      i = 0;
    }
      /*
    if (i == 32) {
      lcd.clear();
      //lcd.setCursor(0,0);
      i = 0;
    }*/
  }

  //while (1)
    //readbuf(buf);

  /*while (!keyboard.available());  
  byte data = keyboard.read();
  while ( data != PS2_KC_ESC ) {
    out.write(&data, 1);
  }*/
  /*
  if(keyboard.available()) {
    byte data = keyboard.read();
    lcd.setCursor(0,0);
    lcd.print(data, HEX);
    // Test for special keys and handle them appropriately
    if(data == PS2_KC_BREAK) {
      Serial.print("[BREAK]");
    } else if(data == PS2_KC_ENTER) {
      Serial.println("");
    } else if(data == PS2_KC_ESC) {
      Serial.print("[ESC]");
    } else if(data == PS2_KC_KPLUS) {
      Serial.print("+");
    } else if(data == PS2_KC_KMINUS) {
      Serial.print("-");
    } else if(data == PS2_KC_KMULTI) {
      Serial.print("*");
    } else if(data == PS2_KC_NUM) {
      Serial.print("[NUMLOCK]");
    } else if(data == PS2_KC_BKSP) {
      Serial.print("[BACKSPACE]");
    } else {
      // Not a special key so print it directly
      Serial.println(data, HEX);
    }
  }*/
  out.close();
}

