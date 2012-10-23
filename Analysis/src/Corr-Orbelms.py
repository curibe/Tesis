# -*- coding: utf-8 -*-
#import numpy as np
#import matplotlib.pyplot as plt
#import os
#import commands as cm
from Analysis import *

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
filenameOE=AnalDir+NameFileOE
a,Q,e,inc=np.loadtxt(filenameOE, usecols=[0,1,2,3],unpack=True)
#***** Tisserand Parameter ******
filenameT=AnalDir+NameFileT
#Tiss=np.loadtxt(filenameT,usecols=[5])
A,Ex,I,Tiss=np.loadtxt(filenameT,usecols=[0,2,3,4],unpack=True)



#==============================
# COUNTING BODIES 
#==============================
"""
The array Nbodies contain the follow parameter
array([TmAm,TmAM,TMAm,TMAM])
where:
TmAm : Number of bodies with Tiss<=3.0 and a<=AJ
TmAM : Number of bodies with Tiss<=3.0 and a>=AJ
TMAm : Number of bodies with Tiss>=3.0 and a<=AJ
TMAM : Number of bodies with Tiss>=3.0 and a>=AJ
"""
Vec=np.loadtxt(filenameT,usecols=[0,4])
Vec[:,0]=Vec[:,0]/AU  # Vec[fila,columna]
# **** Converting from (km,rad) to (AU,deg)******
A=A/AU
I=I*180.0/np.pi
# ************** Counting *******************+
Nbodies=Count_TvsA(Vec)
percent=Nbodies*100.0/Nbodies.sum()
# *********** GENERAING TEXT LABELS *************
TmAmTXT="%.2f "%(percent[0]) + "%"
TmAMTXT="%.2f "%(percent[1]) + "%"
TMAmTXT="%.2f "%(percent[2]) + "%"
TMAMTXT="%.2f "%(percent[3]) + "%"


#**************************
# Converting from km to AU
# and radians to degree
#**************************
a=a/AU
Q=Q/AU

#=================================
# Tisserand curve for Jupiter
#=================================
X=np.arange(1.734,20,0.1)
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
#         SEMIMAJOR AXIS VS EXCENTRICITY Version 2  
#*****************************************************
fig2=plt.figure()
AvsE2=fig2.add_subplot(111)
AvsE2.plot(e,a,'go',EX,X,'--',linewidth=2)
AvsE2.set_xlabel('Excentricity')
AvsE2.set_ylabel('Semimajor Axis (AU)')
AvsE2.set_xlim(0,1.0)
AvsE2.set_ylim(0,15)
AvsE2.set_yticks(range(0,15))
AvsE2.grid(True)




#*****************************************************
#          INCLINATION VS SEMIMAJOR AXIS    
#*****************************************************
fig3=plt.figure()
IvsA=fig3.add_subplot(111)
IvsA.plot(a,inc,'ro')
IvsA.set_xlabel('Semimajor Axis')
IvsA.set_ylabel('Inclination (Deg)')
IvsA.set_xlim(0,10)
IvsA.set_xticks(range(0,10))
IvsA.grid(True)


#*****************************************************
#           INCLINATION VS EXCENTRICITY      
#*****************************************************
fig4=plt.figure()
IvsE=fig4.add_subplot(111)
IvsE.plot(e,inc,'ro')
IvsE.set_xlabel('Excentricity')
IvsE.set_ylabel('Inclination (Deg)')
IvsE.set_xlim(0,1)
IvsE.set_xticks(np.arange(0,1,0.1))
IvsE.grid(True)


#*****************************************************
#           INCLINATION VS SEMIMAJOR AXIS  
#*****************************************************
fig5=plt.figure()
IvsA=fig5.add_subplot(111)
IvsA.plot(a,inc,'bo')
IvsA.set_xlabel('Semimajor axis (AU)')
IvsA.set_ylabel('Inclination (Deg)')
IvsA.set_xlim(0,30)
IvsA.grid(True)


#*****************************************************
#        TISSERAND PARAMETER VS SEMIMAJOR AXIS  
#*****************************************************
x=np.arange(AJ,30,0.1)
y=np.ones_like(x)*3
fig6=plt.figure()
TvsA=fig6.add_subplot(111)
TvsA.plot(A,Tiss,'bo')
#TvsA.fill_between(x,y,0,color='green')
TvsA.set_xlabel('Semimajor axis (AU)')
TvsA.set_ylabel('Tisserand Parameter')
TvsA.set_xlim(0,30)
TvsA.set_ylim(0,10.0)
TvsA.axhline(y=3,color='k',ls='--',lw=1.8)
TvsA.axvline(x=AJ,color='k',ls='--',lw=1.8)
# **************** INCLUDING TEXT LABELS *****************
TvsA.text(2.5,1.0,TmAmTXT, size=20,ha="center",va="center", 
          bbox=dict(boxstyle="round",
                    ec=(1., 0.0, 0.2),
                    fc=(1., 0.8, 1.0)))
TvsA.text(25.0,1.0,TmAMTXT, size=20,ha="center",va="center", 
          bbox=dict(boxstyle="round",
                    ec=(1., 0.0, 0.2),
                    fc=(1., 0.8, 1.0)))
TvsA.text(2.5,9.0,TMAmTXT, size=20,ha="center",va="center", 
          bbox=dict(boxstyle="round",
                    ec=(1., 0.0, 0.2),
                    fc=(1., 0.8, 1.0)))
TvsA.text(20.0,8.0,TMAMTXT, size=20,ha="center",va="center", 
          bbox=dict(boxstyle="round",
                    ec=(1., 0.0, 0.2),
                    fc=(1., 0.8, 1.0)))
TvsA.grid(True)


#*****************************************************
#        TISSERAND PARAMETER VS ECCENTRICITY
#*****************************************************
fig7=plt.figure()
TvsE=fig7.add_subplot(111)
TvsE.plot(Ex,Tiss,'bo')
TvsE.set_xlabel('Eccentricity')
TvsE.set_ylabel('Tisserand Parameter')
TvsE.set_ylim(0,10.0)
TvsE.axhline(y=3,color='k',ls='--',lw=1.8)
TvsE.grid(True)


#*****************************************************
#        TISSERAND PARAMETER VS INCLINATION
#*****************************************************
fig8=plt.figure()
TvsI=fig8.add_subplot(111)
TvsI.plot(I,Tiss,'bo')
TvsI.set_xlabel('Inclination (deg)')
TvsI.set_ylabel('Tisserand Parameter')
TvsI.set_ylim(0,10.0)
TvsI.axhline(y=3,color='k',ls='--',lw=1.8)
TvsI.grid(True)



plt.show()

