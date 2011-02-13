/*
  This code works on the Arduino platform
 */

#include <LiquidCrystal.h>
#include <Wire.h>     

#define disk1 0x50    //Address of eeprom chip


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.print("Current Temp :- ");
  
}

void loop() {
  get_values();
  delay(50);  
}
void get_values(){
  
  
  
  double total_sum = 0;
  for(int i = 0; i < 60; i++)
  {

    unsigned int address = i++;
    unsigned int address_p = i;
    double T = get_temp();
    double data = T;
    int real_part = (int) data;
    int point_part = (data*100) - ((int)data*100);
    writeEEPROM(disk1, address, real_part);
    writeEEPROM(disk1, address_p, point_part);  

    int read_real_part = readEEPROM(disk1, address);
    int read_point_part = readEEPROM(disk1, address_p);
    
    double recieved_from_eeprom = (read_real_part*100) + (read_point_part);
    recieved_from_eeprom = recieved_from_eeprom/100;

    total_sum = total_sum + recieved_from_eeprom;
/*    Serial.print(T);
    Serial.print(" <- Read from Sensor  ::::     From EEprom(Total so far)->:");
    Serial.print(recieved_from_eeprom);
    Serial.print("   in addresses ->");
    Serial.print(address);
    Serial.print(", ");
    Serial.println(address_p); */
    delay(80);
  }
/*  Serial.print("Total Sum = ");
  Serial.println(total_sum);    */
  double average = 0;
  average = total_sum/30;
  Serial.print("Average = ");
  Serial.println(average);
  
  lcd.setCursor(0,1);
  lcd.print(average);
  lcd.setCursor(6,1);
  lcd.print("* C");

}


double get_temp(){
  int ThermistorPin = 1; // Analog input pin for thermistor voltage
  int Vo; // Integer value of voltage reading
  float R = 1000.0; // Fixed resistance in the voltage divider
  float logRt,Rt,T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; // for stein-hart equation from wikipedia and values found from http://web.cecs.pdx.edu/~gerry/class/EAS199B/howto/thermistorArduino/thermistorArduino.pdf
  Vo = analogRead(ThermistorPin);
  Rt = R*( 1023.0 / (float)Vo - 1.0 );//from stein-hart equation from wikipedia under the thermister arcticle
  logRt = log(Rt);
  T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;  //from stein-hart equation from wikipedia and convert from k to *c
  //lcd.setCursor(0,1);
  //lcd.print(T);
  return T;

}

void writeEEPROM(int deviceaddress, int eeaddress, int data ) {
  Wire.beginTransmission(deviceaddress);
  Wire.send(eeaddress);   
  Wire.send(data);
  Wire.endTransmission();
  delay(5);
}


byte readEEPROM(int deviceaddress, int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.send(eeaddress);   // MSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available()) 
  {
    rdata = Wire.receive();
  }
  return rdata;
}

