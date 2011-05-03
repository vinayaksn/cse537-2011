/*
  This code works on the Arduino platform
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

void setup() {

 
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
   delay(200);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Current Temp :- ");
  lcd.setCursor(6,1);
  lcd.print("* C");
}

void loop() {
  int ThermistorPin = 1; // Analog input pin for thermistor voltage
  int Vo; // Integer value of voltage reading
  float R = 1000.0; // Fixed resistance in the voltage divider
  float logRt,Rt,T;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; // for stein-hart equation from wikipedia and values found from http://web.cecs.pdx.edu/~gerry/class/EAS199B/howto/thermistorArduino/thermistorArduino.pdf
  Vo = analogRead(ThermistorPin);
  Serial.println(Vo);
  Rt = R*( 1023.0 / (float)Vo - 1.0 );//from stein-hart equation from wikipedia under the thermister arcticle
  logRt = log(Rt);
  T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt ) ) - 273.15;  //from stein-hart equation from wikipedia and convert from k to *c
  lcd.setCursor(0,1);
  lcd.print(T);
  delay(100);
}

