import numpy as np
import os
import commands as cm
from Jupiter import *
from Config import *

#==============
# SHORCUTS
#==============
system=os.system
get=cm.getoutput
getdir=os.getcwd
chdir=os.chdir

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

print "*"*50
print "*  Preparing Simulation in each Directory....."
print "*"*50
for i in range(1,Ndir+1):
    dir= RunDir + "run%d/"%i
    chdir(dir)
    system("make clean prepare build > OutRun.dump")
    system("rm OutRun.dump")
    percent=i/float(Ndir)*100.0
    progress(30,percent,'Building  ')
    
