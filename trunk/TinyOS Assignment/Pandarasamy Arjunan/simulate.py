import sys
from TOSSIM import *

tos=Tossim([]);
node=tos.getNode(32);
node.bootAtTime(1);
tos.addChannel("BlinkC", sys.stdout);

while 1:
	tos.runNextEvent()


