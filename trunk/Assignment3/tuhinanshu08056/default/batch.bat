mode COM4 9600
avrdude -P com4 -b 57600 -p m328p    -c AVRISP -F -e -U flash:w:Assn3_EEPROM.hex 
pause