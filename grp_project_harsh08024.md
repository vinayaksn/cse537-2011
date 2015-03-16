# Device Control through Bluetooth #

## Introduction ##
A system where a mobile phone can be used to control electronic appliances or any circuitry connected.The microcontroller and the mobile phone connect through bluetooth over which the communication takes place.The actual switching is done through relays which are interfaced with the mcu and the circuitry involved.The mcu will have a bluetooth module interfaced to it from which it can communicate to a mobile.

## Hardware Required ##
  * Bluetooth Module(Bluelink2 from rhydolabz) to connect to the microcontroller through which communication to the mobile device takes place.
    * Specification of Bluelink2:
      * Support Master & Slave Mode
      * Bluetooth core V2.0 compliant
      * SPP (Serial Port Profile) support
      * Support UART,USB,PCM,I2C interface to host system
      * Encrypted connection
      * Frequency: 2.4~2.524 GHz
      * Built-in Chip antenna
      * Power Supply:  3V3
      * Dimension: 30mm x 14mm x 2.2 mm
      * Serial communications: 9600-115200bps
      * Operating Temperature: -40 ~ +70C
        * Link to the website: http://www.rhydolabz.com/index.php?main_page=product_info&cPath=130_132&products_id=454
  * A mobile device supporting java(specifically jsr 82).
  * Relays to connect to the external ciruitry interfaced with the microcontroller and used as switch.

## Steps ##
  * Interface the bluetooth module to the microcontroller.
  * Build an application for the mobile to connect to the mcu which allows one to choose the device from a list which can then be operated on.
  * Interface relays with the microcontroller and integrate.

## Circuit Diagrams ##
_For interfacing bluetooth module with the MCU:_
![https://cse537-2011.googlecode.com/svn/trunk/Group-projects/harsh08024/embed_diag(2).jpg](https://cse537-2011.googlecode.com/svn/trunk/Group-projects/harsh08024/embed_diag(2).jpg)

_For Relays:_

![http://www.rentron.com/PicBasic/relay-circuit.gif](http://www.rentron.com/PicBasic/relay-circuit.gif)


## Components Involved ##
  * A microcontroller, interfaced with an external bluetooth module to make it bluetooth compatible.
  * Relays (switches that can be controlled through the MCU), interfaced between the appliances and the MCU.
  * A J2ME application, installed on a mobile which can communicate to the MCU and provide a UI for controlling appliances.

## Working ##
  * Initially the mcu is powered on and is ready to be connected.
    * The mobile app searches for the mcu.
  * Once found,a connection is established between the two.
  * When the user switches a device On/Off through the application UI,some data is sent to the mcu.
    * The mcu interprets the recieved data and sends back its status.

## Progress ##
### Week 1(5-10 april 2011) ###
  * Interfaced the bluetooth module(bluelink2) to the microcontroller.
    * used level converter at Tx because bluelink worked on 3.3V.
  * Connected to my laptop(for now) through hyperlink.
### Week 2(11-17 april 2011) ###
  * Wrote an application for device discovery.
  * Made a relay board for testing.
### Week 3 (18-24 april 2011) ###
  * Completed the mobile application and installed it on the phone.
  * Wrote the necessary code for the mcu.
  * Tested it with the relay board using Leds.
### Week 5(2nd May 2011) ###
  * Made another relay board.
  * Tested it on an actual appliance in the lab.

## References ##
  * http://vshamu.wordpress.com/2011/03/20/bluetooth-module-interfacing-with-microcontroller/#comments
  * Datasheet of ATmega328p.(ATmega328p.pdf)
  * http://developers.sun.com/mobility/midp/articles/bluetooth2/
  * Datasheet of bluelink2(_took from samy sir_).
  * http://www.nowires.org/Presentations-PDF/AndreKpresentasjon.pdf
  * http://j2mesamples.blogspot.com/2009/02/how-to-find-active-bluetooth-devices.html