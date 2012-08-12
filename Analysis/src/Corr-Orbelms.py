import numpy as np
import matplotlib.pyplot as plt
import os
import commands as cm

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# UTIL CONSTANT
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
HOURS=3600.0
DAYS=24*HOURS
YEARS=365.25*DAYS
AU=1.49597870700e8 
RSOI=4.8305783e7
RJUP=71492.0
AJ=778219200.0/AU


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
AnalDir=Principal+"/Analysis/"
SrcDir=AnalDir+"src/"


#===========================
# PARAMETERS
#===========================
Nbins=100.0
rangeA={'Min':0,'Max':30}
NameFileOE="OrbElms_SUN.orb"
NameFileT="Tisserand.dat"


#===========================
# LOADING FILES
#===========================
#***** Orbital Elements *******
filenameOE=SrcDir+NameFileOE
a,Q,e,inc=np.loadtxt(filenameOE, usecols=[0,1,2,3],unpack=True)
#***** Tisserand Parameter ******
filenameT=SrcDir+NameFileT
Tiss=np.loadtxt(filenameT,usecols=[5])

#**************************
# Converting from km to AU
#**************************
a=a/AU
Q=Q/AU

#=================================
# Tisserand curve for Jupiter
#=================================
X=np.arange(1.7,20,0.1)
EX=np.sqrt(1-(3-AJ/X)**2*(AJ/(4*X)))


#============================================================
#                        PLOTS
#============================================================

#*****************************************************
#         SEMIMAJOR AXIS VS EXCENTRICITY   
#*****************************************************
fig1=plt.figure()
AvsE=fig1.add_subplot(111)
AvsE.plot(e,a,'go',EX,X,'--',linewidth=2)
AvsE.set_xlabel('Excentricity')
AvsE.set_ylabel('Semimajor Axis (AU)')
AvsE.set_xlim(0,5)
AvsE.set_ylim(0,15)
AvsE.set_yticks(range(0,15))
AvsE.grid(True)


#*****************************************************
#          INCLINATION VS SEMIMAJOR AXIS    
#*****************************************************
fig2=plt.figure()
IvsA=fig2.add_subplot(111)
IvsA.plot(a,inc,'ro')
IvsA.set_xlabel('Semimajor Axis')
IvsA.set_ylabel('Inclination (Deg)')
IvsA.set_xlim(0,10)
IvsA.set_xticks(range(0,10))
IvsA.grid(True)


#*****************************************************
#           INCLINATION VS EXCENTRICITY      
#*****************************************************
fig3=plt.figure()
IvsE=fig3.add_subplot(111)
IvsE.plot(e,inc,'ro')
IvsE.set_xlabel('Excentricity')
IvsE.set_ylabel('Inclination (Deg)')
IvsE.set_xlim(0,1)
IvsE.set_xticks(np.arange(0,1,0.1))
IvsE.grid(True)


plt.show()
