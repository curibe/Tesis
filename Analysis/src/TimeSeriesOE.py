# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import os
import commands as cm
from Analysis import *
from Colors import *
import matplotlib as mpl
from matplotlib.ticker import MultipleLocator, FormatStrFormatter

#=====================================
# GENERAL PARAMETERS OF PLOT
#=====================================
mpl.rcParams['xtick.labelsize'] = 10
majorFormatter = FormatStrFormatter('%.2lf')
majorLocator   = MultipleLocator(5)


#*********************************
# Frame of simulation in order to
# choose the unit system.
# It can be: AU,RSOI,RJUP 
#*********************************
FRAME="AU"
UNITS="years"
dYear=10
MaxYear=50

Name=''
#===========================
# PARAMETERS
#===========================
Nbins=100.0
rangeA={'Min':0,'Max':30}
#NameFileOE="OrbElms_SUN.orb"
Name=argv[1]  # Name of file
print Name
Ndump="salida.txt"
pathName=AnalDir+Name
pathNdump=AnalDir+Ndump


#============================
# READING FILE
#============================
#Nl=int(get("wc -l %s | gawk '{print $1}'"%pathName))
#system("tail -n %d %s > %s"%(Nl-4,pathName,pathNdump))


#===========================
# LOADING FILES
#===========================
#***** Orbital Elements *******
if FRAME=="AU":
  print "in AU"
  Nl=int(get("wc -l %s | gawk '{print $1}'"%Name))
  system("tail -n %d %s > %s"%(Nl-4,Name,pathNdump))
  t,a,e,i,q,Q=np.loadtxt(pathNdump,usecols=[0,1,4,5,2,3],unpack=True)
  
if FRAME=="RJUP":
  print "in RJUP"
  Nl=int(get("wc -l %s | gawk '{print $1}'"%Name))
  system("tail -n %d %s > %s"%(Nl-4,Name,pathNdump))
  t,a,e,i,q,Q=np.loadtxt(pathNdump,usecols=[0,1,2,3,7,8],unpack=True) # This Name must include the path
  a=a*AU/RJUP
  q=q*AU/RJUP
  Q=Q*AU/RJUP
  
if FRAME=="RSOI":
  print "in RSOI"
  Nl=int(get("wc -l %s | gawk '{print $1}'"%Name))
  system("tail -n %d %s > %s"%(Nl-4,Name,pathNdump))
  t,a,e,i,q,Q=np.loadtxt(pathNdump,usecols=[0,1,2,3,7,8],unpack=True) # This Name must include the path
  a=a/RSOI
  q=q/RSOI
  Q=Q/RSOI
#t,a,e,i,peri,node,M,q,Q,Long,f=np.loadtxt(filenameOE,unpack=True)

if UNITS=="years":
  t=t/365.25




#=======================================================
#                     PLOTS
#=======================================================

#**************************
# PLOT PARAMETERS
#**************************
dy=6

fig=plt.figure()
plt.subplots_adjust(hspace=0.1)

#****************************
#  SEMIMAJOR AXIS
#****************************
A=fig.add_subplot(511)
A.plot(t,a)
#*****Stablishing y limits *******
ylim=A.get_ylim()
yticks=[]
lyticks=[]
for ytick in np.linspace(ylim[0],ylim[-1],10):
    yticks+=[ytick]
    lyticks+=["%0.4e"%ytick]
#lyticks[0]=''
A.set_yticks(yticks[:-1])
A.set_yticklabels(lyticks[:-1],size=9)
#******* Labels ********
A.set_ylabel("a (AU)",rotation='horizontal')
#A.yaxis.set_label_coords(1.04,0.5)
#ax.yaxis.set_ticks_position("right")
A.yaxis.set_label_position("right")


#****************************
#  ECCENTRICITY
#****************************
E=fig.add_subplot(512,sharex=A)
E.semilogy(t,e)
#*****Stablishing y limits *******
ylim2=E.get_ylim()
yticks2=[]
lyticks2=[]
for ytick in np.linspace(ylim2[0]+1E-6,ylim2[-1],dy):
    yticks2+=[np.log10(ytick)]
    lyticks2+=["%0.4e"%ytick]
#yticks2[0]=''
L1=plt.gca()
LY=L1.get_yticks()
E.set_yticklabels(LY[:-1],size=10)
#E.set_yticks(yticks[:-1])
#E.set_yticklabels(lyticks[:-1],size=10)
#plt.yticks(size=10)
#********* Labels ********
E.set_ylabel("e",rotation='horizontal')
#E.yaxis.set_label_coords(1.04,0.5)
E.yaxis.set_label_position("right")
 


#****************************
#  INCLINATION
#****************************
I=fig.add_subplot(513,sharex=A)
I.plot(t,i)
#*****Stablishing y limits *******
ylim=I.get_ylim()
yticks=[]
lyticks=[]
for ytick in np.linspace(ylim[0],ylim[-1],dy):
    yticks+=[ytick]
    lyticks+=["%0.4e"%ytick]
#lyticks[0]=''
I.set_yticks(yticks[:-1])
I.set_yticklabels(lyticks[:-1],size=10)
#********* Labels ********
I.set_ylabel("i (deg)",rotation='horizontal')
#I.yaxis.set_label_coords(1.04,0.5)
I.yaxis.set_label_position("right")


#****************************
#  APHELION
#****************************
RQ=fig.add_subplot(514,sharex=A)
RQ.plot(t,Q)
#*****Stablishing y limits *******
ylim=RQ.get_ylim()
yticks=[]
lyticks=[]
for ytick in np.linspace(ylim[0],ylim[-1],dy):
    yticks+=[ytick]
    lyticks+=["%0.4e"%ytick]
#lyticks[0]=''
RQ.set_yticks(yticks[:-1])
RQ.set_yticklabels(lyticks[:-1],size=10)
#********* Labels ********
RQ.set_ylabel("Q (AU)",rotation='horizontal')
#I.yaxis.set_label_coords(1.04,0.5)
RQ.yaxis.set_label_position("right")


#****************************
#  PERIHELION
#****************************
Rq=fig.add_subplot(515,sharex=A)
Rq.plot(t,q,color=CL['Blueviolet'],linestyle='-')
#*****Stablishing y limits *******
ylim=Rq.get_ylim()
xlim=Rq.get_xlim()
yticks=[]
lyticks=[]
for ytick in np.linspace(ylim[0],ylim[-1],dy):
    yticks+=[ytick]
    lyticks+=["%0.4e"%ytick]
#lyticks[0]=''
Rq.set_yticks(yticks[:-1])
Rq.set_yticklabels(lyticks[:-1],size=10)
#********* Labels ********
if UNITS=="years":
   Rq.set_xlabel("time (years)")
else:
   Rq.set_xlabel("time (days)")
Rq.set_ylabel("q (AU)",rotation='horizontal')
#I.yaxis.set_label_coords(1.04,0.5)
Rq.yaxis.set_label_position("right")


xticklabels=A.get_xticklabels()+E.get_xticklabels()+I.get_xticklabels()+RQ.get_xticklabels()
plt.setp(xticklabels,visible=False)



plt.show()
