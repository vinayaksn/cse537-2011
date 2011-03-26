mode COM3 9600
avrdude -P com3 -b 57600 -p m328p    -c AVRISP -F -e -U flash:w:Rx_Tx.hex 
pause