import sys
from TOSSIM import *
from time import sleep

t = Tossim([]);
m = t.getNode(32);
m.bootAtTime(42325232);
t.addChannel("BlinkC", sys.stdout);

while True:
	sleep(0.2);
	t.runNextEvent();

