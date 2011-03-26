#include <SoftwareSerial.h>
#define MAXVALUES 3
#include <LiquidCrystal.h>
#include <Wire.h>     
#define disk1 0x50    //Address of eeprom chip

LiquidCrystal lcd1(12, 11, 7, 6, 5, 4);
LiquidCrystal lcd2(12, 10, 7, 6, 5, 4);

SoftwareSerial rfSerial = SoftwareSerial(8, 13);
int i, j = 0;

int error = 0; // 0 = no error / 1 = error

char others[100];
char weather[100];
int mails, fb, temp;

int bclt = 0;  //0-on/1-off

void sleeper(){
  if(bclt == 0){
    digitalWrite(9, LOW);
    bclt = 1;
  }
  if(bclt == 1){
    digitalWrite(9, HIGH);
    bclt = 0;
  }
}

void ignore(){
  writeEEPROM(disk1, 0, fb);
  writeEEPROM(disk1, 1, mails);
  fb = 0;
  mails = 0;
  print_all(); 
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

int parse(char strInput[], int output[MAXVALUES])
{
   int strPos;
   int outputptr = 0;

   if (strInput[0] != 's')
   {
     return -1;
   }
   else
   {
     if (strInput[1] != ',')
       return -2;
     output[outputptr] = 0;
     for (strPos=2; strInput[strPos]!= 'e'; strPos++)
     {
       if ((strInput[strPos] < '0') || (strInput[strPos] > '9'))
       {
         if (strInput[strPos] == ',')
         {
           outputptr = outputptr + 1;
           output[outputptr] = 0;
         }
         else
         {
           return -2;
         }
       }
       else
       {
         output[outputptr] = output[outputptr]*10 + (strInput[strPos]-'0');
       }
     }
     if (outputptr<MAXVALUES-1)
     {
       return -3;
     }
     else
     {
       return 0;
     }
   }
}

void print_all(){
  
  lcd1.setCursor(0, 0);
  lcd1.print(" Mails = ");
  lcd1.setCursor(10, 0);
  lcd1.print(mails);
  lcd1.setCursor(0, 1);
  lcd1.print(" FB = ");
  lcd1.setCursor(6, 1);
  lcd1.print(fb);  
  
  for(i = 0; i<16; i++){
    lcd2.setCursor(i, 0);
    lcd2.print(weather[i]);
  }
  lcd2.setCursor(0, 1);
  lcd2.print(" Temp. = ");
  lcd2.setCursor(11, 1);
  lcd2.print(temp);
  lcd2.setCursor(14, 1);
  lcd2.print("*C");
  
}

void setup() {
  Serial.begin(9600);
  rfSerial.begin(1200);
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);
  writeEEPROM(disk1, 0, 0);
  writeEEPROM(disk1, 1, 0);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  attachInterrupt(0, sleeper, HIGH); // pin 2 = HIGH, run the sleeper function
  attachInterrupt(1, ignore, HIGH); // pin 3 = HIGH, run the ignore function

}

void loop() {
  
  int result;
  int outArray[MAXVALUES];
  
  if(rfSerial.read() == 's'){  //Gets all the updates
    Serial.println();
   for(i = 0; i<100; i++){
     others[i] = rfSerial.read();
     Serial.print(others[i]);     
     if(others[i] == 'e')
       break;

   }
  
  result = parse(others,outArray);
  if (result==0) 
  {
    mails = outArray[0];
    fb = outArray[1] - readEEPROM(disk1, 0);;
    temp = outArray[2];
    error = 0;
  }
  else
  {
    error = 1;
    Serial.println("Error");
  }
  delay(100);
 } 
  
  if(rfSerial.read() == '#'){  //Gets the weather update
    Serial.println();
   for(i = 0; i<100; i++){
     weather[i] = rfSerial.read();
     Serial.print(weather[i]);
     if(weather[i] == '*')
       break;
   }
     
   for(i = 0; i<100; i++){
     if(weather[i] == '*')
       break;
     Serial.print(weather[i]);
     delay(2);
   }
 }
 
 print_all();
}
