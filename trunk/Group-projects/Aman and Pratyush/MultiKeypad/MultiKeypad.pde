/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

int value=0;
int Pin=13;

int ledPin_1 = 9;                                            // Least Significant Bit
int ledPin_2 = 10; 
int ledPin_3 = 11;                                            // LED Digital pin number
int ledPin_4 = 12; 
int ledPin_5 = 13; 
//int ledPin_6=  you can increase resolution if more pins available.....current resolution is upto 16.....

byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connec t to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  pinMode(ledPin_1, OUTPUT);
 pinMode(ledPin_2, OUTPUT);
   pinMode(ledPin_3, OUTPUT);
 pinMode(ledPin_4, OUTPUT);
   pinMode(ledPin_5, OUTPUT);
   digitalWrite(ledPin_1, LOW);
  digitalWrite(ledPin_2, LOW);
  digitalWrite(ledPin_3, LOW);
  digitalWrite(ledPin_4, LOW);
  digitalWrite(ledPin_5, LOW);
}
  
void loop(){

  
  char key = keypad.getKey();
  
  //  char state=keypad.getState();
  int index=0;
  int x=0;
  int y=0;
  if (key =='*'){
    //key=keypad.getKey();
    key=NO_KEY;
    while(key!='#' && index<=1)
    {
      key=keypad.getKey();
      if (key != NO_KEY)
      {
      //  Serial.println(key);
        x= (int)key;
      //  Serial.println("The corres integer val is:");
      //  Serial.println(x);
    
        x=x-48;
        if(index==0)
        {
          y=x;
        }
        if(index==1)
        {
          x=x+y*10;
        }
      //  Serial.println("Value of x is:");
     //   Serial.println(x);
        if(key!='#')
          index=index+1;
        if(key=='#')
          break;  
      }
      key=NO_KEY;
    }
    //x=y;
   
    if(index==1)
    {
      //Serial.println("Y is:");
      //Serial.println(y);
      x=y;
    }
    
    Serial.println("Final Value of x is:");
    Serial.println(x);
    int ar[6] = {0}; 
    for (int i =0;i<6;i++)
    {
      ar[i] = x%2;
      x=x/2;
    }
    for (int i =0;i<6;i++)
    {
      Serial.println(ar[i]);
    }
    //last element of array is most significant bit.....
    
    if(ar[0]==0)
      digitalWrite(ledPin_1, LOW);
    else
      digitalWrite(ledPin_1, HIGH);
    
    if(ar[1]==0)
      digitalWrite(ledPin_2, LOW);
    else
      digitalWrite(ledPin_2, HIGH);
      
    if(ar[2]==0)
      digitalWrite(ledPin_3, LOW);
    else
      digitalWrite(ledPin_3, HIGH);  
      
    if(ar[3]==0)
      digitalWrite(ledPin_4, LOW);
    else
      digitalWrite(ledPin_4, HIGH);  
      
    if(ar[4]==0)
      digitalWrite(ledPin_5, LOW);
    else
      digitalWrite(ledPin_5, HIGH);  
      
    /*if(ar[5]==0)
      digitalWrite(ledPin_6, LOW);
    else
      digitalWrite(ledPin_6, HIGH);  */
    //delay(1000);
    }
  
}
