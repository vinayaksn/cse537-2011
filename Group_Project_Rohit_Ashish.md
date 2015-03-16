# Introduction #

> Pulsemetry is a non invasive method of measuring a person's pulse. It monitors the person's heart beat rate. A probe is attached to the patients finger or ear lobe comprising LEDs and photo-detector. As the light from the two LEDs (red - 660 nm and infrared - 950 nm) pass through the body tissues to a photo-detector, it is absorbed by blood and soft tissue.


# Theory & Working Principle #

> The light absorption rate at the two wavelengths by the hemoglobin is different and depends on the degree of oxygenation. The light level changes as the blood is pumped by the heart. As a consequence, the oximeter also measures the heart rate in beats per minute (BPM)

**Biometric sensors that can detect pulse and oxygen content in the blood are called Pulse Oximeters.**

The principle of pulse oximetry is based on the red and infrared light absorption characteristics of oxygenated and de-oxygenated hemoglobin. Oxygenated hemoglobin absorbs more infrared light and allows more red light to pass through. De-oxygenated (or reduced) hemoglobin absorbs more red light and allows more infrared light to pass through. Red light is in the 600-750 nm wavelength light band. Infrared light is in the 850-1000 nm wavelength light band.

Pulse oximetry uses a light emitter with red and infrared LEDs that shines through a reasonably translucent site with good blood flow. Opposite the emitter is a photo-detector that receives the light that passes through the measuring site.


# Basic Architecture #

The whole system comprises of two subsystems, namely :-
﻿  a) The Sensor subsystem, and
﻿  b) The Base Station
The Sensor subsystem comprises of IR and Red LEDs, Photo-Detector, RF Transmitters, a low power small size microcontroller(preferably from the ATTiny family, though not fully decided) to keep all these components working in proper manner.

The Base station comprises of RF Receivers, SD cards attached to an SD card reader-writer(to Log data locally), LCDs(to Display Data Real Time), an Ethernet Shield(to log data over the Internet), all joined over together with our Arduino Boards.

# Cut Down Version #

The sensors are worn by the patient in the form of a clip over his finger wherein a photo-detector detects the frequency of light it absorbs that is initially emitted by the IR and the Red LED. This read value is amplified and sent to a base system using RF radios wirelessly. The base system comprises of LCD's to display the result in real time as well as writes the current read data onto an attached SD card and also uploads the same over the Internet so that a remotely located doctor is able to keep track of all his out-station patients. Making the sensor subsystem wireless gives us better manouverability as well as keep it light as majority of the heavy hardware is with the base station.


# Hardware Requirement #

1) For Sensor Subsystem:-
﻿  **RED LED,
﻿** IR Transmitter
﻿  **Photo-Detector(namely TSL235R)
﻿** LM358N Amplifier
﻿  **RF Transmitter(434 Mhz)
﻿** A Micro-Controller i.e. ATMega8L
﻿  **Power Source**

2) For Base Station:-
﻿  **RF Receivers
﻿** Arduino Boards
﻿  **Power Source**

# Stages Of Development #
### Testing for Various Photo Sensors ###
After doing much research on various viable and available photo-sensors, both IR as well as IR-cum-Light sensors, we settled for :
  * 2N5777 Photo-Darlington
> > Even though it's performance was very low, we kept this on hand because of it's easy availability and non-requirement of an external amplifier
  * TSL235R Light to Digital Signal Converter
> > Being very easy to interface, this photo-sensor(worked only on RED LED) also gave quite accurate results,
  * Normal IR receivers
> > Easy Availability, low cost, easy interfacing -> ideal choice

### Testing for Working of the chosen Photo-sensors ###
These Selected photo-sensors gave absurd values in start, but as we proceeded with our research on their working, we were able to interface TSL235R and IR sensors with ease, though the 2N5777 photo Darlington was very difficult to because of it's low on-line support as well as because of it's transistor based multiple capabilities.

### Interfacing the Micro-Controller as Standalone ###
We wanted a minimal configuration of the Micro-Controller Unit so as to reduce upon the size, for this all the UART, external Oscillators, resistors and capacitors were required to be stripped off. We planned to use the Micro-Controllers' internal 8Mhz Oscillator as the main clock source.
Due to this, the module turned out to be very time consuming as at first we got our hands on a ATMega168 with no boot-loader. Though we had success on burning a bootloader in the chip, bu somehow, weren't able to burn programs on it using our Arduino Boards as ISP.

Because of this flaw, we had to move on to a smaller and cheaper Micro-Controller, i.e. ATMega8L, we got online support from http://todbot.com/blog/2009/05/26/minimal-arduino-with-atmega8/ and were easily able to do all the required burning of bootloaders as well as programs to finally get the Micro-Controller be used under our needs.

### Putting All The modules Together ###
After being able to get the modules up and running as standalone, we had to get them working in a small packaging, small enough to worn on hand, though we ultimately had to sacrifice it's being worn capability due to our requirements of having to interface several sensors, so we had to make it in a form of small table gadget, on which we put on our fingers to get the desired results.
#### Mishapping ####
During our soldering exercise of putting every module in one place, we accidentally burnt the TSL235R sensor thus decreasing upon the overall output of our gadget to a very large extent.


# Reference #

1. http://www.oximetry.org/pulseox/principles.htm

2. http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1276174700

3. http://en.wikipedia.org/wiki/Pulse_oximetry