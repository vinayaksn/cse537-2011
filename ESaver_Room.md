# Introduction #

This page describes the details about the ESaver Room Project. It covers all the devices in detail with their respective functionalities.

# Why do we need a ESaver\_room? #

We all waste a lot of power throughout the day due to our carelessness when we don't turn off the small things like fans, lights, ACs etc when we leave the room. How about making a smarter room which can automatically switch off the equipments if there is nobody inside the room and switch them on when somebody enters the room. This project describes how we can use a micro-controller to upgrade our room into a smart electricity saving room.

# Hardware required #
The following are the hardware required:
  1. IR sensors-Rs 30 (Everest sales shop no 629)
![http://elecrom.files.wordpress.com/2008/02/cropir-sensors.jpg](http://elecrom.files.wordpress.com/2008/02/cropir-sensors.jpg)

> 2. Relays -Rs 30 (Everest sales shop no 629)
![http://upload.ecvv.com/upload/Info/200801/China_I_2006315213813493072_PCB_Relays.jpg](http://upload.ecvv.com/upload/Info/200801/China_I_2006315213813493072_PCB_Relays.jpg)

Two types of relay will be used - 5A and 15A for fan and AC

> 3. Ethernet shield -Rs2500
![http://www.liquidware.com/system/0000/1920/Arduino_Ethernet_Shield.jpg](http://www.liquidware.com/system/0000/1920/Arduino_Ethernet_Shield.jpg)

> 4. Piezoelectric Buzzer -Rs 50 (Everest sales shop no 629)
![http://walleymusic.com/inbindi/images/piezo_buzzer.jpg](http://walleymusic.com/inbindi/images/piezo_buzzer.jpg)

> 5. ATmega328 microcontroller
http://iteadstudio.com/store/images/produce/Platform/ATMega328/ATMega328.JPG

> 6. PIR sensor -Rs 250 (Everest sales shop no 629)
![http://www.tech-faq.com/wp-content/uploads/2011/01/PIR-Sensor.jpg](http://www.tech-faq.com/wp-content/uploads/2011/01/PIR-Sensor.jpg)

> 7. contact sensor(slotted optical sensor)-Rs 50 (Everest sales shop no 629)
![http://rocky.digikey.com/weblib/Optek/Web%20photos/OPB960T11.jpg](http://rocky.digikey.com/weblib/Optek/Web%20photos/OPB960T11.jpg)


# Hardware Functionality #

1. IR sensors: the sensors help to identify the presence of number of people entering or leaving the room.

2. Relays: it will be used to operate all the lights and fans in the room.

3. Ethernet Shield: it will be used to inform the user over the internet about the status of the electricity usage in the room.

4. Piezoelectric Buzzer: it creates sound when any movement is detected by proximity sensor

5. LCD: To display the number of people in the room.

6. Contact sensor: tells when the door is opened.

# Hardware Architecture Diagrams #

The following diagrams specify the connections of the the various equipments :

![http://www.ardx.org/src/circ/ARDX-SC-06-150.png](http://www.ardx.org/src/circ/ARDX-SC-06-150.png)

![http://coopy.sproutlab.com/projects/rain-umbrellas/images/rain-one-sensor-circuit-diagram.png](http://coopy.sproutlab.com/projects/rain-umbrellas/images/rain-one-sensor-circuit-diagram.png)

![http://www.sunrom.com/images/media/3565A.jpg](http://www.sunrom.com/images/media/3565A.jpg)

![http://i55.tinypic.com/k2cxm9.png](http://i55.tinypic.com/k2cxm9.png)

# Software #

The software initially written on AVR C with the IR sensor, PIR sensor and the switching the bulb on and off was working untill the ethernet shild came in.
The ethernet sheild requires pins 10-13 to communicate with the Atmega 328 microcontroller hence handling all the registers and setting all the values is quite stringient in AVR environment.
The arduino code has a web server that runs on the ethernet sheild, using which one can turn the lights in a room on/off  with access to the web page, for example you forget to turn the lights off when you leave your office you can now turn them off once you reach home through the web page.
The software has a setup where the ethernet sheild is setup and the loop which takes care of the people entering the room and the web page which is the master switch.

# Steps #

1.Increment the count when someone enters the room. This will be done by the IR sensors.

2.If the count is greater than 0 i.e. there is one or more people in the room turn on all of the appliances.

3.If the count is equal to 0 i.e. there is no one in the room turn off all of the appliances.

5.Through the Ethernet shield send the collected data to the computer, where it can be hoisted on the web. It is also used to automatically turn the appliances in the room on/off.

6.Use PIR sensor to detect movement in the room.

7. A piezo-buzzer to be used as a burglars alarm on detection of  unauthorized entry of any individual in the room.(this situation is when the counter measures 0 number of people in the room and still movement is detected by the PIR sensor).

# Functionality of the system #

When somebody enters into the room then the counter is incremented by one and the light and other appliances in the room will be switched ON. When any one leaves the room then the counter is decremented by one. The light will be switched OFF only when everyone goes out of the room and counter is zero. The total number of persons inside the room is also displayed on the LCD.

Further proximity sensors is used to monitor any movement in the room. In case if the counter reads zero and proximity sensor detects any movement, burglar alarm will switch on, alerting unauthorized intrusion. Also, a contact sensor is used to detect when the door is closed or opened.

A desktop application is used to take this data over network and show the inference (in terms of total number of people in the room, time since last presence was detected using PIR and status of window/door) in real time. Ethernet shield is used to send this data on to the network so that the user can view the status of the appliances and automatically switch the corresponding appliance on/off.

# Learnings #

1. Coding in Arduino.

2. Using the sensors and their interface with the microcontroller.

3. interfacing ethernet shield with the microcontroller.


# Challenges #

1. Setting up the whole system in the real world was very different from the basic setup of our project. (Making the wires not visible and having clean connections)

2. The microcontroller and the wires which we were using in our project were taken by different group and they refused to return it at the time of the demo. We were left with broken wires and did not get to crimp the wires because the other group had taken it from the lab.

3. We were sharing the ethernet shield with 2 other groups.

4. The contact sensor we bought did not work as the IR rays were not emitted by the emitter in the sensor.


# Acknowledgenment #

We would like to thank Dr.Amarjeet Sir for guiding us in making the ESaver Room. A special thanks to Mr.Abhishek Bharadwaj and Sammy sir for clearing our doubts and making the work easier by providing us with lab equipments on time.