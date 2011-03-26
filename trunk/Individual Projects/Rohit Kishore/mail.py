import serial, sys, feedparser
import time
import os
import urllib
import urllib2
from xml.dom import minidom

OPWeatherUrl = 'http://weather.yahooapis.com/forecastrss?w=1094645&u=c'

def weather_in_url():
    try:
        dom = minidom.parse(urllib.urlopen(OPWeatherUrl))
        ycondition = dom.getElementsByTagNameNS('http://xml.weather.yahoo.com/ns/rss/1.0', 'condition')[0]
        return "%s,e#%s*" % (ycondition.getAttribute('temp'), ycondition.getAttribute('text'))
    except:
        ite_err()
        return "Inactive Internet"    
    
    

USERNAME="rtgtheboss@gmail.com"
PASSWORD=""	# Needs to be changed at the time of Demo
PROTO="https://"
SERVER="mail.google.com"
PATH="/gmail/feed/atom"
  
SERIALPORT = "/dev/ttyUSB1" # Change this to your serial port!

USERNAME_1="fb.notify.rohitk@gmail.com"

try:
	ser = serial.Serial(SERIALPORT, 1200)
except serial.SerialException:
	print "Error"
	sys.exit()
	print "No Serial Connection, but will continue :P"


  
newmails = int(feedparser.parse(PROTO + USERNAME + ":" + PASSWORD + "@" + SERVER + PATH)["feed"]["fullcount"])
facebook = int(feedparser.parse(PROTO + USERNAME_1 + ":" + PASSWORD + "@" + SERVER + PATH)["feed"]["fullcount"])

for s in range(0, 100):
	ser.write('0b01010101')
ser.write("ss,"+str(newmails)+","+str(facebook)+","+str(weather_in_url()))

print "ss,"+str(newmails)+","+str(facebook)+","+str(weather_in_url())

ser.close()

