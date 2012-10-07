# -*- coding: utf-8 -*-
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
Tiss=np.loadtxt(filenameT,usecols=[4])


#**************************
# Converting from km to AU
#**************************
a=a/AU
Q=Q/AU



#=========================================
# DEFINING MAXIMUM AND MINIMUM
#=========================================
#************ Semimajor Axis************
if a.max()>rangeA['Max']:
    MaxA=rangeA['Max']
else:
    MaxA=np.ceil(a.max())
MinA=np.floor(a.min())
#dxA=(MaxA-MinA)/Nbins
dxA=1.0
#************ Aphelion******************
MaxQ=np.ceil(Q.max())
MinQ=np.floor(Q.min())
dxQ=(MaxQ-MinQ)/Nbins
#************ Eccentricity *************
MaxE=np.ceil(e.max())
MinE=np.floor(e.min())
dxE=(MaxE-MinE)/Nbins
#************ Inclination **************
MaxI=np.ceil(inc.max())
MinI=np.floor(inc.min())
dxI=(MaxI-MinI)/Nbins
#************ Tisserand ***************
MaxT=np.ceil(Tiss.max())
MinT=np.floor(Tiss.min())
dxT=(MaxT-MinT)/Nbins



#=========================================
#        DEFINING BINS
#=========================================
#************ Semimajor Axis***********
BinA=np.arange(MinA,MaxA+dxA/2.0,dxA)
dimA=len(BinA-1)
inA=BinA.searchsorted(a.max())
if a.max()>rangeA['Max']:
    Alim=rangeA['Max']
else:
    Alim=BinA[inA]
#************ Aphelion******************
BinQ=np.arange(MinQ,MaxQ+dxQ/2.0,dxQ)
dimQ=len(BinQ-1)
inQ=BinQ.searchsorted(Q.max())
#Qlim=BinQ[inQ]
#************ Eccentricity *************
BinE=np.arange(MinE,MaxE+dxE/2.0,dxE)
dimE=len(BinE-1)
inE=BinE.searchsorted(e.max())
#Elim=BinE[inE]
#************ Inclination **************
BinI=np.arange(MinI,MaxI+dxI/2.0,dxI)
dimI=len(BinI-1)
inI=BinI.searchsorted(inc.max())
#Ilim=BinI[inI]
#************ Tisserand ***************
BinT=np.arange(MinT,MaxT+dxT/2.0,dxT)
dimT=len(BinT-1)
inT=BinT.searchsorted(Tiss.max())
#Tlim=BinI[inT]


#=====================================================================
#                              PLOTS    
#=====================================================================

#****************************************************
#                 SEMIMAJOR AXIS
#****************************************************
fig1=plt.figure()
Adist=fig1.add_subplot(111)
NA=Adist.hist(a,BinA,color='blue',alpha=0.75,histtype='stepfilled')[0]
Adist.set_xlim([MinA,MaxA])
Adist.set_xlabel('Semimajor Axis (AU)')
Adist.set_ylabel('Number of Objects')


#****************************************************
#                    APHELION
#****************************************************
fig2=plt.figure()
Qdist=fig2.add_subplot(111)
NQ=Qdist.hist(Q,BinQ,facecolor='green',alpha=0.75,histtype='stepfilled')[0]
Qdist.set_xlim([MinQ,MaxQ])
Qdist.set_xlabel('Aphelion (AU)')
Qdist.set_ylabel('Number of Objects')


#****************************************************
#                    ECCENTRICITY
#****************************************************
fig3=plt.figure()
Edist=fig3.add_subplot(111)
NE=Edist.hist(e,BinE,color='red',alpha=0.75,histtype='stepfilled')[0]
Edist.set_xlim([MinE,MaxE])
Edist.set_xlabel('Eccentricity')
Edist.set_ylabel('Number of Objects')


#****************************************************
#                    INCLINATION
#****************************************************
fig4=plt.figure()
Idist=fig4.add_subplot(111)
NI=Idist.hist(inc,BinI,color='magenta',alpha=0.75,histtype='stepfilled')[0]
Idist.set_xlim([MinI,MaxI])
Idist.set_xlabel('Inclination (rad or deg)')
Idist.set_ylabel('Number of Objects')


#****************************************************
#                TISSERAND PARAMETER
#****************************************************
fig5=plt.figure()
Tdist=fig5.add_subplot(111)
NT=Tdist.hist(Tiss,BinT,color='cyan',alpha=0.75,histtype='stepfilled')[0]
Tdist.set_xlim([MinT,MaxT])
Tdist.set_xlabel('Tisserand Parameter')
Tdist.set_ylabel('Number of Objects')


plt.show()







