import numpy as np
import os
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

#==============
# PATHS
#==============
HOME=get("echo $HOME")
InitDir=HOME+"/Projects/Tesis/Cond_Iniciales"
Principal=HOME+'/Projects/Tesis'
Actual=Principal+"/BIN"
RunDir=Principal+"/RUNDIR"

#===========================
# CREATING RUNS DIRECTORIES
#===========================
com='wc '+InitDir+'/Io.pos | cut -f 4 -d \" \"' 
cmd='wc '+InitDir+'/StateInit.state | cut -f 4 -d \" \"'
NDIR=int(get(cmd))
ND=int(get(com))
chdir(Principal)
system("bash DirBuild.sh %d"%NDIR)
chdir(Actual)




#================================
# CREATING CONFIGURATION FILES
#================================

#cmd="ls "+InitDir+"/*.pos"
#filesPos=get(cmd)
#N=len(filePos)



# OPEN STATE FILES FOR EACH BODY
#--------------------------------------
nbod=len(Bodyin)
States=np.zeros([nbod+1,ND,6])  

for k in range(nbod):
    path=InitDir+"/"+Bodyin[k]
    X=np.loadtxt(path,usecols=(i for i in range(1,7)))
    States[k]=X
    
#Xio=np.loadtxt(InitDir+"/Io.pos",usecols=(i for i in range(1,7)))
#Xeuropa=np.loadtxt(InitDir+"/Europa.pos",usecols=(i for i in range(1,7)))
#Xganymede=np.loadtxt(InitDir+"/Ganymede.pos",usecols=(i for i in range(1,7)))
#Xcalixto=np.loadtxt(InitDir+"/Calixto.pos",usecols=(i for i in range(1,7)))
#Xsun=np.loadtxt(InitDir+"/Sun.pos",usecols=(i for i in range(1,7)))

#%%%%%%%%%%%%%%%%%%%%%%%
# Loading times
#%%%%%%%%%%%%%%%%%%%%%%%
et=np.loadtxt(InitDir+"/JupiterPos.dat",usecols=[0])
Time['Start']=np.loadtxt(InitDir+"/StateInit.state",usecols=[0])
#Time['Start']=np.loadtxt(InitDir+"/JupiterPos.dat",usecols=[0])
Time['End']=ETF

#%%%%%%%%%%%%%%%%%%%%%%%%
# Loading Comet's States
#%%%%%%%%%%%%%%%%%%%%%%%%
CometState=np.loadtxt(InitDir+"/StateInit.state",usecols=(i for i in range(1,7)))

N=len(et)
Bodies=list()
for body in Bodyin:
    obj=body[:-4].upper()
    obj=eval(obj)
    Bodies.append(obj)

#Bodies=[IO,EUROPA,GANYMEDE,CALIXTO,SATURN,SUN]
#States=[Xio,Xeuropa,Xganymede,Xcalixto,Xsun]





for i in range(NDIR):
    
    j=i%N
    Id=0
    #print "i: ",i
    ofile=open("system.config","a")
    HeadConfig(Time,i+1,ofile,i)
    CentralBody(JUPITER,ofile)
    MinorBody(Id+1,CometState[i],ofile)
    for cuerpo in range(len(Bodies)):
        Id=cuerpo+2
        BodyConfig(Bodies[cuerpo],States[cuerpo][j],Id,ofile)


    TailConfig(ofile)
    ofile.close()
    Description(Time,i)
    # MOVING THE CONFIGURATION FILE TO THE CORRESPONDING RUN DIR
    cmd="mv system.config " + RunDir + "/run%d/"%(i+1)
    cmd2="mv Description.txt "+ RunDir + "/run%d/"%(i+1)
    #print cmd
    system(cmd)
    system(cmd2)
