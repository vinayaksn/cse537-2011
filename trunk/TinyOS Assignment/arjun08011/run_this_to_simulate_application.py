import sys
from TOSSIM import *
from time import sleep

t = Tossim([]);
m = t.getNode(32);
m.bootAtTime(9013435366);
t.addChannel("BlinkC", sys.stdout);

while True:
	sleep(0.02);
	t.runNextEvent();

