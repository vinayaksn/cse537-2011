mode COM2 9600
avrdude -P com2 -b 57600 -p m328p    -c AVRISP -F -e -U flash:w:328_temp_display.hex 
pause