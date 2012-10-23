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
var=vars()

#==============
# PATHS
#==============
#HOME=get("echo $HOME")
Principal=getdir()
#InitDir=Principal+"/Cond_Iniciales/"
#BinDir=Principal+"/BIN/"
#RunDir=Principal+"/RUNDIR/"
TestDir=Principal+"/output/"

#cmd="ls -d "+RunDir+"* | wc -l"
#Ndir=int(get(cmd))


BODIES=loadDesc("Ref2Ref.conf")

FileB=[b+".pos" for b in BODIES["BChange"]]

FileC=BODIES["Central"][0]+".pos"


chdir(TestDir)
Ndump="salida.txt"

vr=list()


# READING FILES
for name in FileB:
    vr.append(name[:-4])
    Nl=int(get("wc -l %s | gawk '{print $1}'"%name))
    system("tail -n %d %s > %s"%(Nl-4,name,Ndump))
    cmd="%s=np.loadtxt('%s')"%(name[:-4],Ndump)
    exec(cmd)

# Central Body
Nc=int(get("wc -l %s | gawk '{print $1}'"%FileC))
system("tail -n %d %s > %s"%(Nc-4,FileC,Ndump))
cmd="%s=np.loadtxt('%s')"%(BODIES["Central"][0],Ndump)
exec(cmd)


for j in range(len(FileB)):
    Rn=list()
    for i in range(Nl-4):
        #print i
        x=var[BODIES["BChange"][j]][i][1]-var[BODIES["Central"][0]][i][1]
        y=var[BODIES["BChange"][j]][i][2]-var[BODIES["Central"][0]][i][2]
        z=var[BODIES["BChange"][j]][i][3]-var[BODIES["Central"][0]][i][3]
        vx=var[BODIES["BChange"][j]][i][4]-var[BODIES["Central"][0]][i][4]
        vy=var[BODIES["BChange"][j]][i][5]-var[BODIES["Central"][0]][i][5]
        vz=var[BODIES["BChange"][j]][i][6]-var[BODIES["Central"][0]][i][6]
        t=var[BODIES["Central"][0]][i][0]
        Rn.append([t,x,y,z,vx,vy,vz])
    np.savetxt(FileB[j][:-4]+".ref",Rn,fmt="%10.5f  %16.8E  %16.8E  %16.8E  %16.8E  %16.8E  %16.8E")

chdir(Principal)
