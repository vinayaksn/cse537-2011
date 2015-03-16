ZigBee is a specification for a suite of high level communication protocols using small, low-power digital radios based on the IEEE 802.15.4-2003 standard for Low-Rate Wireless Personal Area Networks (LR-WPANs), such as wireless light switches with lamps, electrical meters with in-home-displays, consumer electronics equipment via short-range radio needing low rates of data transfer.

Mesh networking (topology) is a type of networking where each node must not only capture and disseminate its own data, but also serve as a relay for other sensor nodes, that is, it must collaborate to propagate the data in the network.

# Introduction #

In this Project we will form a Mesh network of ZigBee Nodes which will used to pass sensory data from multiple node to Master Node. Each Zigbee node will be interfaced with sensors. Sensory data collected from these nodes will pass to Master Node using this mesh network.

# Objectives #
  * Make a point to multipoint and mesh network of ZigBee nodes.
  * Configuring ZigBee coordinator and router
  * Interfacing sensors (temperature or motion) to each node and deploy the network and collecting data.
  * Collecting and plotting the data


# Hardware Design and Setup #
Interfacing micro-controller and XBee for customized operation
We interfaced XBee note to Atmega 328p micro-controller with the minimum component. The things required were 5V voltage regulator, RC crystal of 12 MHz. First attach the Crystal to Port B pin 6 and 7.
Connect the RX,TX of XBee module to RX,TX of Micro-controller. Connect the Vcc and ground of XBee and Microcontroller to 5V regulator. The following Diagram illustrates the connection for better understanding .

STEP1: Designing Power supply for ZigbEE breakout board
Need a L7805 5V voltage regulator, 2 ceramic capacitor for smoothing out the output of L7805
![http://i55.tinypic.com/2l8f2fp.jpg](http://i55.tinypic.com/2l8f2fp.jpg)






STEP2: Attcahing Microcontroller IC holder and Crystal to PCB board
![http://i54.tinypic.com/2jf0v3n.jpg](http://i54.tinypic.com/2jf0v3n.jpg)


Step3: Attaching Xbee adapter to board



![http://i55.tinypic.com/33dz9mc.jpg](http://i55.tinypic.com/33dz9mc.jpg)




Step4:Complete board with Xbee module



![http://i54.tinypic.com/v5iyqo.jpg](http://i54.tinypic.com/v5iyqo.jpg)












For better understanding backside soldering of board is shown below


![http://i54.tinypic.com/30hlfuw.jpg](http://i54.tinypic.com/30hlfuw.jpg)

<h3>Interfacing Sensor and XBee without any microcontroller</h3>
  * The XBee has 6 usable A/D pins.
  * Using a single ADC pin one can achieve a sampling rate of 1 KHz.
  * The A/D feature can be enabled with the ATDx=2 command where x= 0-5(the A/D pin you wish to use).
  * Vref must be tied to an appropriate voltage (0 < Vref <= Vcc).
  * The sample rate can be set with the ATIR command and is set in units of ms, so ATIR=0xA is a sample rate of 10ms or 100Hz.
  * XBee can buffer up to 93 bytes worth of sample data
  * XBee has 10 bit ADC. So each sample requires 2 Byte Hence maximum of 46 data samples.
  * To set the number of samples to be taken before the data is transmitted, the command is ATIT. Maximum value for this is ATIT=0x2E.
We also have board for custom designed mote. This enable us for easy integration of sensors with Xbee module. Following is the image of board which were designed for easy installation of sensors with Xbee.

![http://i52.tinypic.com/98y79h.jpg](http://i52.tinypic.com/98y79h.jpg)

Following are the images of working Mote
.
![http://i53.tinypic.com/2s0ie85.jpg](http://i53.tinypic.com/2s0ie85.jpg)

The Overall archticture of the system

![http://i54.tinypic.com/8zfaz7.jpg](http://i54.tinypic.com/8zfaz7.jpg)



## Point to multi-point ##
  * Configure a multi-point to to master node.
  * Configure the ADCs in ZigBee node
  * Resolving connection issues
Setting up a Point to MultiPoint network of zigbee module:
> You will need 2 XBee adapter kits, 2 matching-protocol XBee modules, an FTDI cable (or other FTDI breakout board, if you can wire it up correctly) as well as a 0.1uF ceramic capacitor, 10Kohm resistor and NPN transistor. The resistor and capacitor can vary quite a bit if you dont have exact values

Step 1. Configure the transmitter
One XBee will act as the 'reset transmitter', it will be attached to the computer via an FTDI cable and wireless send programming commands to the receiver. Lets set this one up first
Connect up the transmitter adapter with XBee modem to your computer using the FTDI cable

And start X-CTU, just like on the configure page.

![http://ladyada.net/images/xbee/ftdipowered.jpg](http://ladyada.net/images/xbee/ftdipowered.jpg)





































![http://ladyada.net/images/xbee/xctustart.gif](http://ladyada.net/images/xbee/xctustart.gif)



Once you've connected/tested that you can communicate with the modem, go to the configure tab and read in the current setup
Then set the following:
The PAN ID should be some 4 digit hex number that will only be used by these two modems - to prevent confusion
Set the baud rate to 19200 if you're using an Arduino with a 168 chip or older '328p chip. You can check your Arduino documentation to figure out which baud rate to use
Or 57600 if you're using a more recent Arduino with '328p chip.

Next we'll set the Packetization Timeout. This is what determines how long to wait before sending the characters over. We're doing some 'bulk transfer' when sending 10K programs over, so you'll probably want this number high like 10
Set pin D3 to be a digital input And set the Digital IO change detect to FF. Technically you can set it to 0x08, which is the mask to listen for only D3 but this certainly works fine.

Now the transmitter is set up to send the current status of pin D3 to any listening modems.
Now solder in a tiny jumper between the RTS pin and D3. This will tie the status of D3 to the status of the RTS pin which is can be configured to be used as the 'arduino reset pin'

Finally setup the FTDI cable so that the RTS pin will reset the Arduino. For Mac/Linux it will already be done but if you're using Windows you'll need to make a slight change to the driver preferences. In the Device Manager, select the USB COM port Then right click and select Properties

Click on the Port Settings tab, and click on Advanced...

Make sure Set RTS On Close is selected. Click OK.
Step 2. Configure the receiver
Now we will set up the other XBee so that it will listen to changes on pin D3. Connect it to the FTDI cable and read in the current configuration just like the first one.
The PAN ID should match the transmitter's

Set the baud rate to 19200 or 57600 to match the transmitter, again


OR

Next we'll set the Packetization Timeout. This is what determines how long to wait before sending the characters over. We're doing some 'bulk transfer' when sending 10K programs over, so you'll probably want this number high like 10


Set pin D3 to be a digital output, default high.

Set the I/O Output to Disabled. This will prevent the receiver from displaying the status update in the serial line and instead just toggle the matching pin.

Finally, set I/O line passing input address to FFFF. If you set up unique addresses for the receiver and transmitter xbees, of course you should change this to match but FFFF will match all addresses.


Now write the changes to the receiver XBee.
Step 3. Wire up the receiver The transmitter XBee connects directly to the FTDI cable/computer and the receiver is wired to the target Arduino. Here I use a half-sized breadboard and rubber band since not much space is necessary. Solder a wire from pin D3 on the receiver XBee adapter, so that you can plug it into the breadboard. This is the mirrored reset line from the transmitter Xbee.

Xbee's are pretty weak and dont have the oomph to reset an Arduino on their own, so we need to wire it up to a transistor which will do the heavy lifting of pulling the reset line down. Pretty much any small NPN transistor will work just fine here. Put a 0.01uF to 0.1uF capacitor in series with the wire from the XBee, and connect the other side to the NPN transistor base. The emitter of the transistor connects to ground. Put a resistor around 10K between the base and emitter. This will pull down the base to keep the Arduino from resetting accidentally.


The collector then goes the Arduino's reset line. Make sure the grounds are all connected, and that the XBee is wired from the Arduino's 5V line

Now power the Arduino either through the USB cable or from a DC supply. That's it! Now you can reprogram it and also watch the serial monitor from more than 100 feet away. Don't forget the serial monitor -must- be at the same baud rate as programming because the XBees can only talk at their configured baud rate.You can also use AVRdude 'out of the box' which I prefer because you get a nice little progress bar. Simply go to the directory where your sketch is stored and look for the .hex file in the applet subfolder



For a correct setting of a ZigBee Network , the following items must be set
1.	ID - PAN ID : must be the same
2.	DL - Destination Address Low :
1.	Coordinator set to FFFF(broadcast mode)
2.	Router set to 0(The default Address Low for Coordinator)
3.	BD - Baud Rate : must be the same

# References #
  * http://www.sparkfun.com/datasheets/Wireless/Zigbee/XBee-Datasheet.pdf
  * http://antipastohw.blogspot.com/2009/01/xbee-shield-to-xbee-shield.html
  * http://arduino.cc/playground/Shields/Xbee012
  * https://sites.google.com/site/xbeetutorial/
  * http://www.johnhenryshammer.com/WOW2/pagesHowTo/networkOverview.php#index