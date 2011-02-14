// With inputs taken from Arduino playground and 10kohms
#include <Wire.h>     
#include <LiquidCrystal.h>

#define disk1 0x50    //Address of 24LC256 eeprom chip

int i = 0;
LiquidCrystal lcd(12, 11, 10, 4, 5, 6, 7);

void setup(void){
  Serial.begin(9600);
  Wire.begin();   
}

void loop(){
  int d = 90;
  if (i == 60) {
    int r = 0;
    for (int j = 0; j < 60;) {
      r += (readEEPROM(disk1, j++) << 8);
      r += (readEEPROM(disk1, j++) & 0xFF);
    }
    r /= 30;
    lcd.setCursor(0,0);
    lcd.print(r);
    Serial.print("Last 30 average: ");
    Serial.println(r, DEC);
    d--;
    i = 0;
  }
  int temp = (analogRead(3) * 100.0 * 5.0 / 1024.0);
  writeEEPROM(disk1, i++, temp >> 8);
  writeEEPROM(disk1, i++, temp & 0xFF);
  Serial.print("Current reading: ");
  Serial.println(temp, DEC);
  delay(d);
/*  if (i==256) {
    i = 0;
    address=0;
  }
  writeEEPROM(disk1, address, i);
  Serial.print(readEEPROM(disk1, address), DEC);
  Serial.print('\n');
  delay(500);
  ++i;
  ++address;
  */
}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {
  Wire.beginTransmission(deviceaddress);
  //Wire.send((int)(eeaddress >> 8));   // MSB
  Wire.send((int)(eeaddress & 0xFF)); // LSB
  Wire.send(data);
  Wire.endTransmission();

  delay(5);
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;

  Wire.beginTransmission(deviceaddress);
  //Wire.send((int)(eeaddress >> 8));   // MSB
  Wire.send((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(deviceaddress,1);

  if (Wire.available()) rdata = Wire.receive();

  return rdata;
}
