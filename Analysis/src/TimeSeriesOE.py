import numpy as np
import matplotlib.pyplot as plt
import os
import commands as cm
from Analysis import *
from Colors import *



#===========================
# PARAMETERS
#===========================
Nbins=100.0
rangeA={'Min':0,'Max':30}
#NameFileOE="OrbElms_SUN.orb"
Name=argv[1]
Ndump="salida.txt"
pathName=SrcDir+Name
pathNdump=SrcDir+Ndump

#============================
# READING FILE
#============================
Nl=int(get("wc -l %s | gawk '{print $1}'"%pathName))
system("tail -n %d %s > %s"%(Nl-4,pathName,Ndump))
NameFileOE=Ndump


#===========================
# LOADING FILES
#===========================
#***** Orbital Elements *******
filenameOE=SrcDir+NameFileOE
t,a,e,i,q,Q=np.loadtxt(filenameOE,usecols=[0,1,2,3,7,8],unpack=True)
#t,a,e,i,peri,node,M,q,Q,Long,f=np.loadtxt(filenameOE,unpack=True)




#=======================================================
#                     PLOTS
#=======================================================

fig=plt.figure()
plt.subplots_adjust(hspace=0.001)

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
    lyticks+=["%0.3e"%ytick]
lyticks[0]=''
A.set_yticks(yticks[:-1])
A.set_yticklabels(lyticks[:-1],size=9)
#******* Labels ********
A.set_xlabel("time (days)")
A.set_ylabel("a (AU)",rotation='horizontal')
#A.yaxis.set_label_coords(1.04,0.5)
#ax.yaxis.set_ticks_position("right")
A.yaxis.set_label_position("right")


#****************************
#  ECCENTRICITY
#****************************
E=fig.add_subplot(512,sharex=A)
E.plot(t,e)
#*****Stablishing y limits *******
ylim=E.get_ylim()
yticks=[]
lyticks=[]
for ytick in np.linspace(ylim[0],ylim[-1],10):
    yticks+=[ytick]
    lyticks+=["%0.3e"%ytick]
lyticks[0]=''
E.set_yticks(yticks[:-1])
E.set_yticklabels(lyticks[:-1],size=10)
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
for ytick in np.linspace(ylim[0],ylim[-1],10):
    yticks+=[ytick]
    lyticks+=["%0.3e"%ytick]
lyticks[0]=''
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
RQ.plot(t,i)
#*****Stablishing y limits *******
ylim=RQ.get_ylim()
yticks=[]
lyticks=[]
for ytick in np.linspace(ylim[0],ylim[-1],10):
    yticks+=[ytick]
    lyticks+=["%0.3e"%ytick]
lyticks[0]=''
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
Rq.plot(t,q,color=CL['Blueviolet'],marker='o',linestyle='-')
#*****Stablishing y limits *******
ylim=Rq.get_ylim()
yticks=[]
lyticks=[]
for ytick in np.linspace(ylim[0],ylim[-1],10):
    yticks+=[ytick]
    lyticks+=["%0.3e"%ytick]
lyticks[0]=''
Rq.set_yticks(yticks[:-1])
Rq.set_yticklabels(lyticks[:-1],size=10)
#********* Labels ********
Rq.set_ylabel("q (AU)",rotation='horizontal')
#I.yaxis.set_label_coords(1.04,0.5)
Rq.yaxis.set_label_position("right")


xticklabels=A.get_xticklabels()+E.get_xticklabels()+I.get_xticklabels()+RQ.get_xticklabels()
plt.setp(xticklabels,visible=False)

Items=CL.items()
#fig2=plt.figure(figsize=(5,10))
fig2=plt.figure()
fig2.subplots_adjust(top=0.99, bottom=0.01, left=0.2, right=0.99)
x=np.arange(0.0,1.0,0.1)
y=np.ones_like(x)
for i in range(10):
    ax=plt.subplot(10,1,i+1)
    #plt.axis("off")
    ax.fill_between(x,y,1.0)
    #ax.patch.set_facecolor(Items[i][1])




plt.show()
