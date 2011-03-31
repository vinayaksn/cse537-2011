mode com2 9600
avrdude -P com2 -b 57600 -p m328p    -c AVRISP -F -e -U flash:w:328_HIH4030.hex 
pause