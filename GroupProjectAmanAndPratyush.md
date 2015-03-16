# Introduction #


Whenever a guest comes into our college building his first point of interaction is the guard. He tells to the guard about the faculty he wants to meet with . The guard either makes a phone call or personally goes to the faculty to tell him about the guest.
We propose an alternate design to deal with the guests. We will use a simple keypad and an Ethernet shield along with our micro controller to connect the reception area with each faculty.


# Details #

Week Wise progress of our Group :

1. Week 1 : Learning to interface Arduino Ethernet Shield with the micro-controller and letting it function as a network Entity.

2. Week 2 : It was spent trying to interface the keypad and allow functionality such as taking in multiple key inputs from the keyboard.

3. Week 3: Putting the whole thing together, designing the daemon running on the faculty's terminal .

The project details are explained in following parts

## Application Design ##
The whole System Design is as follows.

1. The guest comes in and punches the key combination corresponding to the faculty he wants to meet.(key combination for different faculties can be printed on a sheet and put up on the reception desk)

2. Based on the keys pressed the concerned faculty will automatically get notified via a pop up on the browser . The pop up on the browser will be a web page. This task is achieved by a daemon running on the faculty's terminal. We have programmed and created that daemon. (It is Designed in java so it will work on all the platforms)

3. The web page will have two options . He can click either one of them based on the action he wants to take. Either he can ask the guest to come in , or he can ask him to wait.

4. Once the faculty chooses the option , and clicks the submit button ,
the guest on the other side is sees the response on the LCD screen in the reception area.

## Hardware characteristics ##
1. The Keypad being used is a very basic arduino keypad

2. The Ethernet sheild acts as a server and its the one hosting the web page where the faculty gives his response to the guest.

3. The Ethernet shield is given a mac address and the Ip address of its own. However to ensure security , we can put the value of subnet such that the ethernet shield is accessed by just the teachers.

## Challenges ##
1. Interfacing the keypad with the Microcontoller.

2. Sending the keypress information over the Ethernet.

3. Automatically refreshing the HTML page hosted on the Ethernet Shield.

## Softwares used ##
1. Arduino to program on the microcontroller

2. Java to build the daemon running on the faculty's terminal at all times.

3. HTML to make the web page.

## Hardwares used ##
1. Arduino Keypad

2. Atmeage328p microcontroller

3. Arduino Ethernet Shield.

4. LCD screen


# References #

http://www.arduino.cc/en/Main/ArduinoEthernetShield

http://arduino.cc/playground/Code/Keypad

http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1206024602