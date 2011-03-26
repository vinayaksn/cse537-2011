#include <SPI.h>
#include <math.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };       //physical mac address
byte ip[] = { 192, 168, 1, 110 };			   // ip in lan
byte gateway[] = { 192, 168, 1, 1 };			   // internet access via router
byte subnet[] = { 255, 255, 255, 0 };                      //subnet mask
Server server(80);                                         //server port

int ledPin_1 = 4;                                            // LED Digital pin number
int ledPin_2 = 5;                                            // LED Digital pin number

String readString = String(30);                            //string for fetching data from address
boolean LEDON_1 = false;                                     //LED status flag
boolean LEDON_2 = false;                                     //LED status flag
void setup()
{
 Ethernet.begin(mac, ip, gateway, subnet);                 //start Ethernet
 pinMode(ledPin_1, OUTPUT);                                  //Set pin 4 to output 
 pinMode(ledPin_2, OUTPUT);                                  //Set pin 5 to output 
 Serial.begin(9600);                                       //enable serial data print 
 server.begin(); 

}

void loop(){

  Client client = server.available();                        // Create a client connection
  
  if (client) 
  {
    while (client.connected()) 
      {
         if (client.available()) 
         {
          char c = client.read();
          if (readString.length() < 50)                     //read char by char HTTP request
          {
             readString+=c;                                 //store characters to string 
          }  
       
          //Serial.print(c);                                  //output chars to serial port
        
          if (c == '\n')                                    //if HTTP request has ended
          {
           if(readString.indexOf("L1=1")>0)                 //lets check if LED should be lighted
             {                                              //led has to be turned ON    
             digitalWrite(ledPin_1, HIGH);                    // set the LED on
             LEDON_1 = true;
             }
             else if(readString.indexOf("L1=0")>0)
             {                                              //led has to be turned OFF
             digitalWrite(ledPin_1, LOW);                     // set the LED OFF
             LEDON_1 = false;             
             }
             
           if(readString.indexOf("L2=1")>0)                 //lets check if LED should be lighted
             {                                              //led has to be turned ON    
             digitalWrite(ledPin_2, HIGH);                    // set the LED on
             LEDON_2 = true;
             }
             else if(readString.indexOf("L2=0")>0)
             {                                              //led has to be turned OFF
             digitalWrite(ledPin_2, LOW);                     // set the LED OFF
             LEDON_2 = false;             
             }
            
  
            //Measure Current Temp
  /*double temp = analogRead(0);  // Read sensor
  double Temp;
  // See http://en.wikipedia.org/wiki/Thermistor for explanation of formula
  Temp = log(((10240000/temp) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;           // Convert Kelvin to Celcius
*/
          int ThermistorPin = 0; // Analog input pin for thermistor voltage
          int Vo; // Integer value of voltage reading
          float R = 1500.0; // Fixed resistance in the voltage divider
          float logRt,Rt,T;
          float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; // for stein-hart equation from wikipedia and values found from http://web.cecs.pdx.edu/~gerry/class/EAS199B/howto/thermistorArduino/thermistorArduino.pdf
          Vo = analogRead(ThermistorPin);
          Rt = R*( 1023.0 / ((float)Vo - 1.0) );//from stein-hart equation from wikipedia under the thermister arcticle
          logRt = log(Rt);
          T = ( 1.0 / (c1 + c2*logRt + c3*logRt*logRt*logRt)) - 273.15;  //from stein-hart equation from wikipedia and convert from k to *c

  
          client.println("HTTP/1.1 200 OK");                // now output HTML data starting with standart header      
          client.println("Content-Type: text/html");
          client.println();
          
          client.println("<h1>LED-1 control</h1>");           //controlling led via checkbox
                                                            //address will look like http://192.168.1.110/?L=1 when submited
          client.println("<form method=get name=LED><INPUT TYPE=RADIO name=L1 value=1>ON<BR> <INPUT TYPE=RADIO name=L1 value=0>OFF<BR>");                                                 
           
          //printing LED-1 status
          client.print("<font size='4'>Current LED-1 status: ");
          if (LEDON_1)
              client.println("<font color='green' size='5'>ON"); 
          else
              client.println("<font color='red' size='5'>OFF");     
          
          client.println("</font color>");
          client.println("<hr />");
          
          
          //LED-2 Control and Status
          client.println("<h1>LED-2 control</h1>");           //controlling led via checkbox
          client.println("<form method=get name=LED><INPUT TYPE=RADIO name=L2 value=1>ON<BR> <INPUT TYPE=RADIO name=L2 value=0>OFF<BR>");
          client.println("<INPUT TYPE=SUBMIT VALUE=submit></form>");          
          
          //printing LED-2 status
          client.print("<font size='4'>Current LED-2 status: ");
          if (LEDON_2)
              client.println("<font color='green' size='5'>ON"); 
          else
              client.println("<font color='red' size='5'>OFF");     
          
          client.println("</font color>");
          client.println("<hr />");
          client.println("<hr />");
          
          
          client.println("<h1>Current Temperature is: <h1>");
          client.print(T);
          client.print("*C");
          client.println("</body></html>");
          readString="";                                    //clearing string for next read
          client.stop();                                    //Stopping Client
            }
          }
        }
      }
 }     

