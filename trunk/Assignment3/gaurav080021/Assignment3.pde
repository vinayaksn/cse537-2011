#include <LiquidCrystal.h>
#include <Wire.h>        //Arduino I2C library
#define eeprom_addr 0x50 //Address of the 24LC08 eeprom chip
#define thermostat_in 0

// initialise the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
   
  Serial.begin(9600);
    Serial.println("In Code ");
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,LOW);   // GRD for thermistor
  digitalWrite(7,HIGH);  // Vcc for thermistor
  digitalWrite(8,LOW);   // GRD for eeprom
  digitalWrite(9,HIGH);  // Vcc for eeprom
  Wire.begin();          // Initialise the I2C library
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  //lcd.print("\"Gaurav\"");
  }

void loop() {
  
  int count;
  for(count=0;count<30;++count)
   {
   int Vo;
   Vo = analogRead(thermostat_in);
   double Temp;
   Temp = log(((10240000/Vo) - 10000));
   Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
   Temp = (Temp - 273.15)+ 49 ;       // Convert Kelvin to Celcius
   
   writeEEPROM(eeprom_addr, count, Temp); // Write temperature data to eeprom chip
   //lcd.print(Temp);
   delay(90);
  }
  float av_temp;
  for(count=0;count<30;++count)
   {
    av_temp += (float)readEEPROM(eeprom_addr, count); // Read temperature data from eeprom
    delay(5);   
   }
   av_temp=av_temp/30;
   lcd.clear();
   
   lcd.print("Mean Temperature:");
   lcd.setCursor(0,1);
   lcd.print(av_temp);

   Serial.print(av_temp);
   
}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data )
{
  //Serial.println("In Write ");
  Wire.beginTransmission(deviceaddress); //Notify eeprom chip for data transmission
  Wire.send((int)(eeaddress)); //Publish write address  
  Wire.send((int)data); //Forward data to write 
  Wire.endTransmission(); //Notify end of transaction
  //Serial.println("Out Write "); 
  delay(5);
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress )
{
  Serial.println("In read");
  byte rdata = 0xFF;
 
  Wire.beginTransmission(deviceaddress);
  Wire.send((int)(eeaddress));
  Wire.endTransmission();
 
  Wire.requestFrom(deviceaddress,1);// Request for 1(second argument) byte of data stored at the notified address(eeaddress).
 
  if (Wire.available()) rdata = Wire.receive();//Receive data if avilable
  
  return rdata;
}

/*
References:
1. http://10kohms.com/arduino-external-eeprom-24lc256
2. http://arduino.cc/en/Reference/Wire 
3. http://www.sullivan-county.com/ele/pdf/24lc08.pdf
*/


