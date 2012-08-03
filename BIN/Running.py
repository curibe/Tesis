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
Argv=sys.argv
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

if (len(Argv)>1):
    N=int(Argv[1])
    for i in range(1,N+1):
        dir= RunDir + "run%d/"%i
        chdir(dir)
        system("make run")
    
else:
    for i in range(1,Ndir+1):
        dir= RunDir + "run%d/"%i
        chdir(dir)
        system("make run >> RunOut.txt")# >> RunOut.txt
        system("rm RunOut.txt")
        percent=i/float(Ndir)*100.0
        progress(30,percent,'Running   ')
