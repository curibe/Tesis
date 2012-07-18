import numpy as np
import os, sys
import commands as cm

#==============
# SHORCUTS
#==============
system=os.system
get=cm.getoutput
getdir=os.getcwd
chdir=os.chdir
Argv=sys.argv


if (len(Argv)>1):
    N=int(Argv[1])
    print "N=%d"%N
    
else:
    print "No se introdujo ningun valor"


chdir("RUNDIR/run1/output")
system("ls")
