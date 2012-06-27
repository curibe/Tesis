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


#=================================
# READING OUPUT FILES
#=================================
'''
Here, The program read each output file (BODY7.pos), in order to find
the time in what the comet cross the Sphere Of Influence. 

'''
File = "BODY7.pos"
Fdump="Comet.dat"

Tcap=list()
TCapture=list()




for i in range(1,Ndir+1):

    dir=RunDir+"run%d/output/"%i
    Desc=RunDir+"run%d/Description.txt"%i
    chdir(dir)
    Nl=int(get("wc -l %s | gawk '{print $1}'"%File))
    system("tail -n %d %s > %s"%(Nl-4,File,Fdump))
    

    #*******************************
    # Loadind Descripion file and
    # BODY7.pos
    #*******************************
    Times=loadDesc(Desc)
    State = np.loadtxt(Fdump)
    
    for j in range(len(State)):
        R=State[j][7]
        if R>=1.5*RJUP/AU:
            Tcapture=(Times["Start"]+State[j][0])/365.25 + 2000.0
            Row1=np.hstack([State[j],i])
            Row2=np.hstack([Tcapture,i])
            Tcap.append(Row1)
            TCapture.append(Row2)
            break

    


#################################
# SAVING CAPTURE FILE
#################################
chdir(Principal)
Tcap=np.array(Tcap)
TCapture=np.array(TCapture)
print "Saving file..."
np.savetxt("TimeOutSOI.txt",Tcap,fmt="%.5E")
np.savetxt("CaptureTime.txt",Tcap,fmt="%.5f")
        
    


