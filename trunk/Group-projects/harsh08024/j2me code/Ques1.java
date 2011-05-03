import java.io.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.io.*;
import javax.bluetooth.*;
import javax.bluetooth.ServiceRecord;


public class Ques1 extends MIDlet implements CommandListener,DiscoveryListener {
      private List mainScreen;
      private boolean debug=false;
      private Command exit,refresh,ON,OFF;
      private Display display;
      private LocalDevice local=null;
      private DiscoveryAgent agent = null;
      //ServiceRecord[] servicesFound = null;
      private static String service_str;
      private boolean serverFound;
   UUID RFCOMM_UUID = new UUID(0x0003);
   UUID SPP=new UUID(0x1101);
    private StreamConnection m_StrmConn;
    private OutputStream m_Output;
    private InputStream m_Input;
    private DataInputStream in;
    private DataOutputStream out;
    private RemoteDevice remoteDev;
private int status_inquiry=9;


      public void startApp() {
            display = Display.getDisplay(this);
            mainScreen = new List("Device Control..",List.IMPLICIT);
refresh=new Command("REFRESH",Command.OK,0);
ON=new Command("ON",Command.OK,0);
OFF=new Command("OFF",Command.OK,0);
            exit = new Command("Exit", Command.EXIT, 0);
            mainScreen.addCommand(exit);
            mainScreen.setCommandListener(this);
            //mainScreen.append("connecting...", null);
            try {
                  local = LocalDevice.getLocalDevice();
            } catch (Exception e) {
            }
           // if (debug)
            mainScreen.append("Looking for Devices....", null);
            doDeviceDiscovery();
            display.setCurrent(mainScreen);
      }

      public void pauseApp() {
      }

      public void destroyApp(boolean unconditional) {
            notifyDestroyed();
      }

      public void commandAction(Command cmd, Displayable disp) {
           
            if (cmd==ON){
                switch(mainScreen.getSelectedIndex()){
                   
                    case 0:
                        send(0x10);
                            break;
                    case 1:     //  mainScreen.append("22", null);
                        send(0x01);
                        break;
                    case 2:send(0x02);
                        //mainScreen.append("33", null);
                            break;
                    case 3: send(0x03);
                            break;
                       
                }
                updateStatus(getStatus());
            }
            if (cmd==OFF){
            switch(mainScreen.getSelectedIndex()){

                    case 0:
                        send(0x00);
                            break;
                    case 1:     //  mainScreen.append("22", null);
                    send('n');
                        send(0x01);
                        
                        break;
                    case 2:send('n');
                    send(0x02);

                        //mainScreen.append("33", null);
                            break;
                    case 3:send('n');
                        send(0x03);
                            break;
                }
            updateStatus(getStatus());
            }
            if(cmd==refresh){
            updateStatus(getStatus());
            }
                if (cmd == exit) {
                  destroyApp(false);
                }
      }
      public void inquiryCompleted(int param) {
          String str=null;
          switch (param) {
                  case DiscoveryListener.INQUIRY_COMPLETED:
                        //fall through
                   case DiscoveryListener.INQUIRY_TERMINATED:
                   if (remoteDev!=null){
                          doServiceSearch(remoteDev);
                   str="completed or terminated";
                   }
                   else str="no dev found";
                                              break;
               case DiscoveryListener.INQUIRY_ERROR:
                       str="inquiry error";
                        break;
            }
          if (debug)
          mainScreen.append(str, null);
      }

      public void serviceSearchCompleted(int transID, int respCode) {
          String string="nuthin";
            switch (respCode) {
                  case DiscoveryListener.SERVICE_SEARCH_COMPLETED:
                      string="service search completed";
                        break;
                  case DiscoveryListener.SERVICE_SEARCH_DEVICE_NOT_REACHABLE:
                                            string="service search not reachable";
                        break;
                  case DiscoveryListener.SERVICE_SEARCH_ERROR:
                       string="service search not error";
                        break;
                  case DiscoveryListener.SERVICE_SEARCH_NO_RECORDS:
                       string="service search no records";
                        break;
                  case DiscoveryListener.SERVICE_SEARCH_TERMINATED:
                       string="service search terminated";
                        break;
            }
            if (debug)
          mainScreen.append(string, null);

          if(serverFound)
      {
            try
            {   //lets the communication start by setting the url and send client reponse
                m_StrmConn = (StreamConnection) Connector.open(service_str);

                m_Output = m_StrmConn.openOutputStream();
                out=new DataOutputStream(m_Output);
                m_Input = m_StrmConn.openInputStream();
                in=new DataInputStream(m_Input);
mainScreen.append("Connection Established", null);
    }
            catch (IOException ex)
            {
                ex.printStackTrace();
            }

      }
               updateStatus(getStatus());
mainScreen.addCommand(ON);
mainScreen.addCommand(OFF);
mainScreen.addCommand(refresh);

       
          display.setCurrent(mainScreen);
          /*for(int i=0;i<150;i++){
          //send(0);
          }
  while(true){
dataEx();}*/
      }

      public void servicesDiscovered(int transID, ServiceRecord[] serviceRecord) {
        //  mainScreen.append("service discovered", null);
         for (int i = 0; i < serviceRecord.length; i++)
    {
        service_str = serviceRecord[i].getConnectionURL(ServiceRecord.NOAUTHENTICATE_NOENCRYPT, false);
//mainScreen.append(service_str, null);
        System.out.println(service_str);
        if(service_str.startsWith("btspp")) 
        {
            serverFound = true;
            agent.cancelServiceSearch(transID);
            mainScreen.append(".", null);
    if (debug)
            mainScreen.append("service found...", null);
             break;
        }

    }
          
      }

      public void deviceDiscovered(RemoteDevice remoteDevice, DeviceClass deviceClass) {
            String str = null;
            try {
                  str = remoteDevice.getFriendlyName(false);

                  if (str!=null)
                     mainScreen.append(""+str,null);
                 

            } catch (Exception e) {
                mainScreen.append("remote device friendly name exception",null);
            }
            //activeDevices.append(remoteDevice.getBluetoothAddress(),null);

            
           // activeDevices.append(""+devicesFound.isEmpty(), null);
                if (str.equals("AUBTM-20")){
              //if (debug)
                    mainScreen.append("Device Found.", null);
                     remoteDev=remoteDevice;
                     agent.cancelInquiry(this);
                 
                //     doServiceSearch(remoteDevice);
                      }
      }

      private void doDeviceDiscovery() {

          try {
                  local = LocalDevice.getLocalDevice();
            } catch (BluetoothStateException bse) {
                   // Error handling code here
            }
            agent = local.getDiscoveryAgent();
            try {
                  if (!agent.startInquiry(DiscoveryAgent.GIAC, this)) {
                        // Inquiry not started, error handling code here
                  }
            } catch (BluetoothStateException bse) {
                  // Error handling code here
            }
      }

      private void doServiceSearch(RemoteDevice device) {
           
           UUID uuidSet[] = new UUID[1];
      uuidSet[0] =  RFCOMM_UUID;
      //uuidSet[0]=SPP;
        try {
           // if (debug)
            mainScreen.append("looking for services...", null);
            agent.searchServices(null, uuidSet, device, this);
        } catch (BluetoothStateException ex) {
 
        mainScreen.append("bluetoothstateexception", null);
            ex.printStackTrace();
        }
        
      }
 
private void dataEx() {
String mess;
byte b=-1;
int outbyte = 0x09;
 
 try {

         out.writeByte(outbyte);
         out.flush();
        } catch (IOException ex) {mainScreen.append("out io exception", null);

            ex.printStackTrace();
        }
       try {
            b = in.readByte();
            //in.reset();
        } catch (IOException ex) {mainScreen.append("in io exception", null);
 
            ex.printStackTrace();
        }
}
private int send(int outbyte){

try {
         out.writeByte(outbyte);
         out.flush();
        } catch (IOException ex) {mainScreen.append("out io exception", null);

            ex.printStackTrace();return -1;
        }
 return 1;
}
private int recieve(){
byte b=-1;
    try {            b = in.readByte();
            //in.reset();
        } catch (IOException ex) {mainScreen.append("in io exception", null);
 
            ex.printStackTrace();
        }
    return b;
    }
private int getStatus(){
    int res=-2;
    send(status_inquiry);
    res=recieve();
    return res;

}
private void updateStatus(int status){
String first,sec,third,on="ON",off="OFF";
if((status&1)==0)
    first=off;
else first=on;

if((status&2)==0)
    sec=off;
else sec=on;

if((status&4)==0)
    third=off;
else third=on;

mainScreen.deleteAll();
mainScreen.append("All", null);
           // mainScreen.append("Switch all ON", null);
            mainScreen.append("device 1 is "+first, null);
            mainScreen.append("device 2 is "+sec, null);
          //  mainScreen.append("device 3 is "+third, null);
mainScreen.setSelectedIndex(0, true);
//mainScreen.append(first+""+sec+""+""+third, null);
}

}
