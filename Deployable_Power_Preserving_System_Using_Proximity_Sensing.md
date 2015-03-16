# Introduction #

A problem regularly faced by computer users is bad resolution of power saving in monitor. Here by bad resolution I mean that either we can keep a small timer for turning off display which would be troublesome while reading a pdf or watching a movie or we can keep long time which would end in wasting a lot of power. This problem motivated us to think of a solution which should detect your presence and hence make the monitor utilize power only when it is necessary and also ensure usability for the user which means he doesn’t have to again and again press a key or move the mouse to wake up the monitor.
The real world application of this project is such that after thinking of this project I recently saw a company coming up with computers that detect your presence and hence save power.

# Details #

## Approach ##

The power supply of the monitor would have a relay attached to it which will regulate when to supply power and when to cut it off. The relay would be connected to a Passive Infrared sensor which will detect the presence of a user. An Important thing to be kept in mind is that for an application like this the proximity of the sensor should be less and more suited for a computer usage requirement.
The switch board of the monitor would also be connected to a current sensor will basically measure the power consumption of monitor which would be a good thing to do for estimating the value for money of the device and also for making users realize the amount of electricity wasted in such activities. The current sensor will convert the drop/rise in current to drop/rise in voltage.  A microcontroller will take this drop in voltage as an ADC input and thus calculate the power consumed by the monitor also this microcontroller would also be connected to the relay and IR sensor and will direct the relay to switch on or off the power.
The microcontroller would also store the daily power consumption of the device and the power saved by this system in a SD card and this information will be useful in the estimation of the amount of electricity saved by the system thus giving the value for money of the system.

## Implementation Plan ##

_First deadline_

Interfacing the IR sensing module with the micro-controller and experimenting to discover the optimal threshold values and the optimal sensing frequency for the IR module.

_Second deadline_

Addition of a configuration button through which a user can always change the optimum distance from the monitor of that particular user. This requires the user to press the button and sit in the optimum position in front of the system. The system after some delay will start sensing the optimum distance and take the average value for 5 seconds and set this as a new threshold in the system. Since the value would be stored in EEPROM, the threshold would be preserved even if the system is switched off.



## _System Components_ ##

### Micro controller Board (ATMEGA 328p) ###

### IR Sensor (Sharp GP2Y0A02YK0F) ###

Features

1. Distance measuring range : 20 to 150 cm

2. Analog output type

3. Package size : 29.5×13×21.6 mm

4. Consumption current : Typ. 33 mA

5. Supply voltage : 4.5 to 5.5 V

### RGB LED ###

### Relay Switch (5V) ###

### Current Sensor ###

### System controlled Electric Plug Board ###



## _Circuit Diagram_ ##

![https://lh3.googleusercontent.com/-AuhJ-9yMpJI/TbxueNVeR_I/AAAAAAAAABE/cvQdw2Mo8to/s912/mbed_project_fig.jpg](https://lh3.googleusercontent.com/-AuhJ-9yMpJI/TbxueNVeR_I/AAAAAAAAABE/cvQdw2Mo8to/s912/mbed_project_fig.jpg)




## Hardware Requirements ##

Microcontroller Board: ATMega328p (already have)

IR Sensor : Infrared Proximity Sensor Long Range - Sharp GP2Y0A02YK0F
Price : Rs. 880
/-http://www.rhydolabz.com_index.php?main_page=product_info&cPath=137_150&products_id=469_

Relay Switches.


Current Sensor: ACS712 Current Sensor.



## System Applications ##

1. Touch-less switch
(Sanitary equipment, Control of illumination, etc. )

2. Sensor for energy saving
(ATM, Copier, Vending machine, Laptop computer,
LCD monitor)

3. Amusement equipment
(Robot, Arcade game machine)