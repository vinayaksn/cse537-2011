# Aim & Applications #

Energy efficient vehicles can cut your travel costs, reduce your greenhouse gas emissions, and make you healthier. Keeping these points in mind, the aim of the project is to add features to our cars to make them eco friendly and user friendly by providing low cost solutions. Following are the features:

  1. Detection of high smoke level inside the car and take appropriate           actions.
  1. Analyze driving pattern of the driver in real time to give a feedback on the route and driving pattern.
  1. Automatic Temperature control in the car.
  1. Assistance in car parking.

The EHCB(Energy and Health Car Buddy) helps conserve energy by giving feedback of the driving pattern and monitoring the performance of the Air condition. It helps to keep a check on the air pollution level in the car, in order to give passengers a pollution free ride and even assist the driver in parking the vehicle.




# Motivation #

  1. Our aim is to create a multifunctional device that would at least be  useful to us and we will love to put it in our cars.
  1. It is a fact that improving mileage would compromise safety is untrue, increasing fuel efficiency would cost consumers significantly more. EHCB would be cheap and the return on investment would be really good as it’s highly useful thing.
  1. Automobiles, 2nd biggest factor after industry to contributing to global warming by producing green house gases such as: CO, CO2, NO2, CH4 (methane).
  1. Low fuel efficiencies make us more vulnerable to oil price spikes and greater use of fuel.
  1. So much pollution in the air, especially on busy roads poses threat to humans.



# Hardware Required #

  1. MMA 7260 3 axis Accelerometer.
  1. Smoke detector: Air quality control sensor, MQ135l.
  1. Temperature Sensor LM35.
  1. LCD 16x2 h.
  1. Motor with Fan as an AC prototype: MOT-1191,12v 500rpm DC motor.
  1. Ultrasonic (distance) sensor.
  1. AVR Board.
  1. 12 V battery.
  1. Fan (for simulation of monitoring of AC).
  1. Pin to convert the voltage provided the car power outlet (12V)to the voltage supported by our avr board(5V).

# Demonstration 1: April 11 #
We planned to deploy our system in the car in the first milestone. The following were demonstrated in the first demo:
  1. Interfaced a light sensor and a fan to the micro controller and adjusted it's speed proportional to the intensity of the light falling on the sensor. We were successfully able to adjust the fan speed and the direction using PWM.
  1. Interfaced the accelerometer and LED to the micro controller and adjusted the intensity of the LED proportional to the acceleration value. If the change in acceleration is very high then the LED would light up to it's maximum intensity indicating warning for wastage of fuel due to poor driving.
  1. We even displayed the accelerometer value, sampled every 1 millisecond on the LCD screen.
  1. The complete system was deployed successfully in the car.

## Improvements Needed ##
For the final demonstration we are supposed to the following :
  1. Adjust the threshold for the PWM of the accelerometer as the LED was lighting up even for a small change in the acceleration.
  1. Interfacing Ultra sonic sensor for the parking assistance.
  1. Interfacing a smoke sensor instead of the light sensor and rotating the fan in anti clockwise direction when the smoke value is high. This will help us change the normal fan to an exhaust fan in case when the smoke level is high in the car.

# Demonstration 2: April 20 #
In this milestone we demonstrated the following:
  1. Interface an ultra sonic sensor along with a buzzer. The sound of the buzzer was adjusted  inversely proportional to the distance of the sensor from any other object.
  1. The sensor was deployed in the car on the back bumper. It was successfully demonstrated in the parking lot of IIIT-Delhi. Distance of 0m to 4m  were detected and feedback to the user was given by the buzzer.



<img src='http://i.imgur.com/pJf10.jpg' />
  1. Figure 1: Parking sensor in action. A car with 4 parking sensors.

# Plan For Final Demonstration: May 3 #
We plan to deliver the complete system with all the components developed in the first two demonstrations. We also plan to put our complete system in a box just showing the LCD, LED, Accelerometer and the Ultra sonic sensor. Hence the deliverable are as follows:
  1. Parking Assistance giving feedback using the Buzzer
  1. Accelerometer sensor with LED intensity as the live feedback to the driver.
  1. The temperature sensor with the temperature value displayed on the LCD
  1. A fan which adjusts it's speed with respect to the temperature value.
  1. The smoke sensor was not working properly and hence we changed it with the temperature sensor. Due to lack of time we were not able to buy a new smoke sensor. In future, We will interface the smoke sensor also to the system and will be used by one of us in his car :):).
<img src='http://i.imgur.com/raNCg.jpg' />
## Challenges ##
  1. Deploying the whole system in the car.
  1. The final iteration required the system to be put in a box. It was challenging to design the box accordingly(with proper holes) and ensure proper working of the system.
  1. Dependency of sensor on weather conditions.
  1. Setting proper thresholds.
  1. Powering the AVR board from the car.
  1. Deploying the whole system using only 1 avr board. This was a challenging task as our system had too many wires and we were falling short of pins. (esp PortC)