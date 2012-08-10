#!usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

#===============
# PARAMETERS
#===============
Nbins=100.0


#==========================
# READING FILE
#==========================
Year=np.loadtxt("CaptureTime.dat", usecols=[4])

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

#N,bins,patches=CapT.hist(Year,BINS,normed=False,facecolor='blue',alpha=0.75)
N,bins=np.histogram(Year,BINS)
Hist=N/float(N.sum())
CapT.bar(BINS[:-1],Hist,dx,alpha=0.8)
CapT.set_xlim([Min,rlim])
CapT.set_xticks(np.arange(Min,rlim,1))
plt.show()
