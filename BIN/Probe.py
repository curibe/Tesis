import numpy as np
import os, sys
import commands as cm
from Jupiter import *
from Config import *
from ICond import *

#==============
# SHORCUTS
#==============
system=os.system
get=cm.getoutput
getdir=os.getcwd
chdir=os.chdir
argv=sys.argv

#==============
# PATHS
#==============
#HOME=get("echo $HOME")
Principal=getdir()
InitDir=Principal+"/Cond_Iniciales/"
BinDir=Principal+"/BIN/"
RunDir=Principal+"/RUNDIR/"

cmd="ls -d "+RunDir+"* | wc -l"
Ndir=int(get(cmd))
Name= argv[1]
print "Name: ",Name
