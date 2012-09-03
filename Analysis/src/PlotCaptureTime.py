# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import os
import commands as cm



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


#===============
# PARAMETERS
#===============
Nbins=100.0
#NameFile=Capture.dat
NameFile="CaptureTime.dat"


#==========================
# READING FILE
#==========================
filename=AnalDir+NameFile
Year=np.loadtxt(filename, usecols=[4])


#********************
# DEFINING BINS
#********************
Max=np.ceil(Year.max())
Min=np.floor(Year.min())
dx=(Max-Min)/Nbins
BINS=np.arange(Min,Max+dx/2.0,dx)
dim=len(BINS)-1
index=BINS.searchsorted(Year.max())
rlim=BINS[index]



#=======================
# PLOT
#=======================
fig=plt.figure()
CapT=fig.add_subplot(111)
#NN,b,p=plt.hist(Year,bins=BINS,weights=np.zeros_like(Year)+1./Year.size)     # Normalized to 1
#N,bins,patches=CapT.hist(Year,BINS,normed=False,facecolor='blue',alpha=0.75)
N,bins=np.histogram(Year,BINS)
Hist=N/float(N.sum())
CapT.bar(BINS[:-1],Hist,dx,alpha=0.8)
CapT.set_xlim([Min,rlim])
CapT.set_xticks(np.arange(Min,rlim,1))
CapT.set_xlabel('Time (years)')
CapT.set_ylabel('Probability of Capture')
plt.show()
