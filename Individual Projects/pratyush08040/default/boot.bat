mode COM6 9600
avrdude -P COM6 -b 57600 -p m328p -c AVRISP -F -e -U flash:w:328_lcd.hex
pause