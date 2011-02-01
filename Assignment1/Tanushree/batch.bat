mode com2 96000
avrdude -P com2 -b 57600 -p m328p -c AVRISP -F -e -U flash:w:test_lcd.hex
pause
