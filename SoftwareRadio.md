# SOFTWARE RADIO #
Software Radio, also known as software-defined radio, is a software problem of building radio components(eg. mixer, detector, modulator/demodulator etc)with the help of software instead of hardware.In other words we can say the aim is to diminish the hardware gap between the software and the antennae, as much as doable, by dissolving the RF hardware in between. This approach increases device  flexibility, simplifies manufacturing and reduces costs.

# Contents #
1. Introduction

2. Purpose of RF front-end

3. Reciever Design and issues

4. Smart Antennas

# 1. Introduction #
Radio devices are almost everywhere around us like FM radios, mobile phones, home automation devices like gate openers & so many others. The motivation behind the software radio approach is that different radio devices can not talk to each other but the software can reconfigure devices on the fly so that they can talk and listen to multiple channels.Software radio approach provides a flexible radio architecture that allows changing the radio personality,possibly in real-time and guarantees a desired quality of service. Which helps us to make out the full utilization of the radio frequency of the electronic spectrum.
Add your content here.

# 2. Purpose of RF front-end #
Of the two sections of transceiver i.e transmitter and receiver , receiver is the most complex and important focus of this approach. The role of receiver is to isolate the incoming signal from external noise and interference for demodulation and further processing.The basic function is to filter out unwanted signal and condition the desired signal for digital processing. This involves extracting signal from antennae, filter it to remove undesired signal, converting signal to an amplitude compatible with the Analog to digital conversion process and finally feeding it to analog to digital converter.

# 3. Reciever Design and issues #

The ideal concept to software radio approach would be to attach an analog-to-digital converter with the antennae. The digital signal processor would read the converter, and then its software would transform the stream of data from the converter to any other form the application requires.
As, the original analog-to-digital converters would not be able to pick a very low power signal (nano-watt, or micro-watt), it should be preceded by a low-noise amplifier in the conversion step. But, these amplifiers introduces problems like if some harmonics, outside the range assigned to transmitter are present in the recieved signal, then these may compete with the desired signal within the dynamic range.This may introduce distortion in the desired signal or may block it.
The solution would be to put band-pass filters b/w antenna and amplifier, but that may reduce the flexibility of the radio-which is considered to be main point of software radio.

# 4. Smart Antennas #

Smart Antennas ( or MIMO (multiple input and multiple output) ) are the antenna arrays enabled with the smart signal processing algorithms & it has basically two functions to perform, one is DOA (direction of arrival) estimation and the other being associated technique with the former function is beamforming.
DOA of signal denotes the direction from where the signal has arrived & its estimation is performed by the associated technique called beamforming which combines the elements in the array of the sensors such that signals at particular angle experience constructive interference while others experience destructive interference.

Benefits of Smart Antennas
i) It supports spatial signal processing

ii) Multiple antennas can be implemented at the sender as well as at the receiver side.

iii) It could be of much use in case where fixed antennas can not work as they automatically optimize the preferred signal direction for each particular broadcast emission.

**NOTE:** There is a research group called Smart Antennas Research Group!. The group focuses on the advancement the state-of-the-art in the applications of multiple antennas and space-time signal processing in mobile wireless networks, and to improve network performance and economics. For more information visit [http://www.stanford.edu/group/sarg/ ](.md).



# Example #

1 GNU Radio

GNU Radio is a free software development toolkit that provides the signal processing at the runtime and processing blocks to implement software radios using readily-available, low-cost external RF hardware and commodity processors.
[http://gnuradio.org/redmine/wiki/gnuradio ](.md)