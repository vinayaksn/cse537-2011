#include <LiquidCrystal.h>
#define TSL_FREQ_PIN 2 // output use digital pin2 for interrupt  
#define READ_TM 100 // for take 10 readings in a second
// two variables used to track time  
 unsigned long cur_time = millis();  
 unsigned long previous_time = cur_time;  
 unsigned int tm_diff = 0;
 unsigned long pulse_cnt = 0;  
 int incomingByte = 0;
 int count=0;
 unsigned long arr[20];
 int timer=0;
 int average=0,gen_avg=90,newData=0;
 LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
 void setup() {  

    
   // attach interrupt to pin2, send output pin of TSL235R to arduino 2  

   // call handler on each rising pulse  
    

 attachInterrupt(0, add_pulse, RISING);  
  pinMode(TSL_FREQ_PIN, INPUT); 
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW); //make an additional ground for backlight purposes
  delay(200);
  Serial.begin(9600);
  lcd.begin(16, 2); 

 }  

    
void loop() {  
   
  previous_time   = cur_time;  
  cur_time   = millis();  



  if( cur_time > previous_time ) {  

     tm_diff += cur_time - previous_time;  

  }  

  else if( cur_time < previous_time ) {  


     tm_diff += ( cur_time + ( 34359737 - previous_time ));  //handling if overflow occurs

  }   
   
   //if defined milliseconds are complete 

  if( tm_diff >= READ_TM ) {  

   

     

    tm_diff = 0;  
    
    if(count==20){ //if 20 readings are complete
      count=0;
      timer++;
     int beats = get_beats();
     Serial.print("Beats ");
     Serial.print(beats);
     beats=beats*30;
    
     for(int i=0;i<20;i++)
     {
       arr[i]=0;
     }
     
     if(average==0)
      average=beats;
      else
       average = (average+beats)/2;
         lcd.clear();
         if(newData==0)
        lcd.print("Sensing.....");
        else{
         lcd.print("Pulse Rate = ");
         lcd.print(gen_avg);
        }
       if(timer==5)
       {
         timer=0;
        lcd.clear();
       gen_avg=(average+gen_avg)/2;
      
       lcd.print("Pulse Rate = ");
       lcd.print(gen_avg);
       average=0;
       newData=newData=1;
       
    }

   }   // get our current frequency reading  
  
    unsigned long frequency = get_tsl_freq(); 
   
   arr[count]=frequency;
    count++;
   
   // lcd.clear();
    //lcd.print(frequency);
   
  
    //Serial.print(timepassed);
    Serial.print(" "); 
    Serial.println(frequency);    
   
   
 

  }  
 

}  


 void add_pulse() {  

 pulse_cnt++;  

  return;  
 } 
 
 unsigned long get_tsl_freq() {  


   unsigned long freq = pulse_cnt* 100;   

   pulse_cnt = 0;  

   return(freq);  

} 

int get_beats()
{
  int beats=0;
  int tag[20];
  unsigned long maximum=0;
  unsigned long threshold=0;
   for(int i=1;i<20;i++)
  {
    if(arr[i]>maximum)
    maximum=arr[i];
  }
  Serial.print("maximum = ");
  Serial.println(maximum);
 
   threshold=maximum-200;
    Serial.print("Threshold = ");
  Serial.println(threshold);
  for(int i=1;i<20;i++)
  {
    tag[i]=0;
  }
  for(int i=1;i<20;i++)
  {
  
   if(arr[i]>=threshold)
   {
     if(i==1)
     {
     beats=beats+1;
     tag[i]=1;
     }
     else if(tag[i-1]==0)
     {
       beats=beats+1;
       tag[i]=1;
     }
       
   }
  
  }
 return(beats);
 
}

 
