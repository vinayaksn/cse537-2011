    #include <SPI.h>
    #include <Ethernet.h>
    //#include <LiquidCrystal.h>
    
    
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };    
    byte ip[] = { 192, 168, 4, 24 };
    byte gateway[] = { 192, 168, 4, 1 };
    byte subnet[] = { 255, 255, 255, 0 };         
    Server server(80);                                        
    //LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
    String readString = String(70);                            //string for fetching data from address
    int Pin_1 = 0;                                            // Least Significant Bit
    int Pin_2 = 1; 
    int Pin_3 = 2;                                            // LED Digital pin number
    int Pin_4 = 3; 
    int Pin_5 = 4; 
    int val1=0;
    int val2=0;
    int val3=0;
    int val4=0;
    int val5=0;
    int keyread=0;
    char *a;
    
    bool Contains( String s, String search)
    {
    int max = s.length() - search.length(); 
    for (int i=0; i<= max; i++)
    {
     if (s.substring(i) == search) return true; 
    }
    return false; 
    }
    
    
    
    void setup()
    {
     Ethernet.begin(mac, ip, gateway, subnet);           
     Serial.begin(9600);
     server.begin(); 
    // lcd.begin(16, 2);
    
    }
    
    void loop(){
    Client client = server.available();
      
    val1=analogRead(Pin_1);  // least significant bit...
    val2=analogRead(Pin_2);
    val3=analogRead(Pin_3);
    val4=analogRead(Pin_4);
    val5=analogRead(Pin_5);
    Serial.println("Start Printin");
      Serial.println(val1);
      Serial.println(val2);
      Serial.println(val3);
      Serial.println(val4);
      Serial.println(val5);
    Serial.println("End Printin");
    
  //---------------------------------------------------  
    if(val1>1000)
      val1=1;
    else
      val1=0;
      
    if(val2>1000)
      val2=1;
    else
      val2=0;
      
    if(val3>1000)
      val3=1;
    else
      val3=0;
      
    if(val4>1000)
      val4=1;
    else
      val4=0;
      
    if(val5>1000)
      val5=1;
    else
      val5=0;
      
    keyread=val1+val2*2+val3*4+val4*8+val5*16;
  //---------------------------------------------------    
    
    Serial.println("keyread is :");
    Serial.println(keyread);
  
    /*char buff[50];
    char *temp;
    char *temp1;
    sprintf(buff,"%d",keyread);
    Serial.println("string is");
    Serial.println(buff);*/
      if (client)
      {
       // Serial.println("hi i m here");
         boolean currentLineIsBlank = true;
         
        while (client.connected())
          {
             if (client.available())
             {
               
              char c =client.read();
            
             if (readString.length() < 50)                     //read char by char HTTP request
              {
               readString+=c;                                 //store characters to string 
              }  
              else
              {
                Serial.println(readString);
                /*if(Contains(readString,"fname"))
                  {
                    Serial.println("Print fname");
                    Serial.println(readString.indexOf("fname"));
                  }*/
                if(readString.indexOf("Wait")>0)
                  {
                    //display on LCD
                //    lcd.print("Wait");
                    Serial.println("Wait Selected");
                  }  
                  
                if(readString.indexOf("Comein")>0)
                  {
                //    lcd.print("Comein");
                    //display LCD
                    Serial.println("Comein Selected");
                  }  
                readString="";
              }
               //Serial.println(c);             
                if(c=='\n')
                {
                  
                  
                client.println("HTTP/1.1 200 OK");
                client.println("Content-Type: text/html");
                client.println();
                client.print("<form method=get name=response>");//<input type=radio name=Status value=Amarjeet>Amarjeet<br><input type=radio name=Status value=Ashish>Ashish<br>");//<input type=radio name=Status value=Ok>---------------<br>");
                //client.print("<input type=radio name=Status value=Busy>------------<br>");
                //client.println("<input type=submit value=submit></form>");
    //            client.print("<input type=radio name=Status value=Amarjeet>Amarjeet<br>");
    //            client.print("<input type=radio name=Status value=Ashish>Ashish<br>");
    //            client.print("<input type=radio name=Status value=Pushpendra>Pushpendra<br>");
    //            client.print("<input type=radio name=Status value=Vinayak>Vinayak<br>");
                //client.print("<input name=Status value=Vinayak>Vinayak<br>");
    //            client.println("<a href=192.168.4.24 return false>HTML color chart</a>");
                //Serial.println("jhdagfjagdfjadjfvgsdjkjksdabvkdajvkajvfjksv");
                //itoa(keyread,a,10);
                //Serial.println(*a);
           //     temp=(char *)malloc(sizeof(char *))
                //temp=strcat("<input type=hidden name=Status value=",buff);
                //temp1=strcat(temp,">Vinayak<br>");
    //              client.print("<input type=hidden name=Status value="+p+">Vinayak<br>");              
    //Serial.println(temp1);
    //Serial.println("gvdghsgdjhfgdsjgfjksdgfjsgdjvfgskjdgvfjksdgkjfvsdkjkvfjsgbkjvbsf");
                //Serial.println(*temp1);
                //client.print("<input type=hidden name=Status value=");
                //client.print(buff);
                //client.print(">Vinayak<br>");
                //client.print(*temp1);            
                //client.print("<input type=radio name=Status value=keyread><br>");
                
    
                if(keyread==1)
                {
                  client.print("<input type=hidden name=Status value=Amarjeet><br>");              
                }
    
                if(keyread==2)
                {
                  client.print("<input type=hidden name=Status value=Vinayak><br>");              
                }
                
                
                if(keyread==3)
                {
                  client.print("<input type=hidden name=Status value=Pushpendra><br>");              
                }
    
                if(keyread==4)
                {
                  client.print("<input type=hidden name=Status value=Ashish><br>");              
                }
                
                if(keyread==5)
                {
                  client.print("<input type=hidden name=Status value=Shishir><br>");              
                }
                
                if(keyread==6)
                {
                  client.print("<input type=hidden name=Status value=Mayank><br>");              
                }
                
                if(keyread==7)
                {
                  client.print("<input type=hidden name=Status value=Richa><br>");              
                }
                
                if(keyread==8)
                {
                  client.print("<input type=hidden name=Status value=Anirban><br>");              
                }
                
                if(keyread==9)
                {
                  client.print("<input type=hidden name=Status value=PK><br>");              
                }
    
                if(keyread==10)
                {
                  client.print("<input type=hidden name=Status value=Astrid><br>");              
                }
                
                if(keyread==11)
                {
                  client.print("<input type=hidden name=Status value=Somitra><br>");              
                }
                
                if(keyread==12)
                {
                  client.print("<input type=hidden name=Status value=Vivek><br>");              
                }
                
                if(keyread==13)
                {
                  client.print("<input type=hidden name=Status value=Anuradha><br>");              
                }
                
                if(keyread==14)
                {
                  client.print("<input type=hidden name=Status value=Pankaj><br>");              
                }
                
                if(keyread==15)
                {
                  client.print("<input type=hidden name=Status value=Aman><br>");              
                }
                
                if(keyread==16)
                {
                  client.print("<input type=hidden name=Status value=Pratyush><br>");              
                }
                
                if(keyread==17)
                {
                  client.print("<input type=hidden name=Status value=Tanmay><br>");              
                }
                
                if(keyread==18)
                {
                  client.print("<input type=hidden name=Status value=Vibhas><br>");              
                }
                
    
                //client.println("<input type=text name=fname /><br />");
                
                client.print("<input type=radio name=selection value=Wait>Wait<br>");
                client.print("<input type=radio name=selection value=Comein>Comein<br>");
//                client.print("<input type=radio name=Status value=Pushpendra><br>");
    
                client.println("<input type=submit value=submit></form>");
                client.println("</body></html>");
                
                keyread=0;
                
                client.stop();
                }
                 
              //c=client.read();
              //Serial.println(c);
              //client.flush();
             // client.stop();
            //}
              }
            }
          }
     }     
      
      
