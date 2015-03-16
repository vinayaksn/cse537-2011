# Week 1 (2 April - 9 April) #
  * Completed mote to PC data transfer module

# Week 2 (10 April - 17 April) #
  * Completed graphing interface
  * Completed serial processing interface
  * Initial phase of web-based UI completed

# Week 3 (18 April - 24 April) #
  * Completed radio interface
  * Fixed errors in the python sdk
  * Created python serial monitor
  * Created ADC interface

# Week 4 (25 April - 3 May) #
  * Final phase of web-UI
  * Completion of networking module
  * Project Completed

# Details #
## Scenario ##
Electricity bills depend upon the energy consumption. Energy consumption is not as explicit to the people and therefore they are often surprised by the huge bill they get. Even though they may not be using a particular device at a particular time, they may forget to switch it off, leading to high power consumption.

## Proposal ##
A system consisting of a network of motes which monitor and control the energy consumption of a place (home, office etc), switching devices on and off at a specified time. This may result into a system which would ensure that the electricity bill does not go beyond a upper limit set by the person.

## System Details ##

  * The individual nodes installed at each output point will read the sensor values of the energy consumption at their respective output points.
  * Every node sends its calculated power consumption to the central node which passes it on to the Server.
  * The central server creates a graph for each node and present energy consumption information to the user .A cumulative consumption of all nodes is also represented.
  * Also,the user can control the power consumption through a user interface at the central server.The system allows the user to set the times during day for which a particular device has to be switched on.The user can also toggle device states at the instant through a click.

## Components of the system ##
  1. Current sensor
> > We considered interfacing one of the following current sensors/transformers to the TelosB mote depending on availability and other factors.
> > http://iteadstudio.com/store/index.php?main_page=product_info&cPath=4&products_id=154
> > http://www.seeedstudio.com/depot/noninvasive-ac-current-sensor-30a-max-p-519.html?cPath=144_154
> > http://www.rhydolabz.com/index.php?main_page=product_info&cPath=137_139&products_id=506&zenid=22995ec3ba8a72aa61dcf65e1b1adb2b


> Finally we interfaced ACS714 current sensor.It is a hall effect based current sensor and works for -5A to 5A AC.The datasheet can be found here http://www.allegromicro.com/en/Products/Part_Numbers/0714/0714.pdf
> The sensor provides analog current readings and were read by TelosB using the TelosB's inbuilt ADC.The sensor works for 4.5V to 5.5V but since the Telosb's maximum specified voltage is 3V we were not able to caliberate the readings.Initially the sensor and mote were powered using separate sources to remain in their specified power source ranges, but when both were powered using 3V , it was found that the ADC readings reflected the variations in actual current consumption.
> > The sensor was interfaced using TinyOS in nesC.

  1. Network
> > All nodes will connect to a central node over an RF network, transmitting the power consumption and toggling state toggling information between each node and the central server.
> > The wireless communication was performed using TinyOS in nesC.

  1. Web-based UI and server
> > The web UI provides the statistics on the power consumption at each node and the total cumulative power consumption at all nodes.It also provides options to let the user specify the times during the day at which the device has to be switched on.Also, the toggling of device's state at the instant can be done on a click.
> > The server has been programmed in HTML,php,python and java.