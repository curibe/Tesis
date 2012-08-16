import numpy as np
import matplotlib.pyplot as plt
import os
import commands as cm
from Analysis import *

#==============================
#          PARAMETERS
#==============================
dT=0.1
dx=0.1
AMin=1.734
AMax=20.0
AMin3=2.0833
T=3.0
T1=3.0+dT
T2=3.0-dT
T3=3.0-dT*10.0
T4=3.0-dT*20.0
T5=3.0-dT*30.0
T6=3.0-dT*40.0
T7=3.0-dT*50.0

#====================================
#  CALCULATING TISSERAND PARAMETERS
#====================================
XE=np.arange(AMin,AMax+dx,dx)
X3E=np.arange(AMin3,AMax+dx,dx)
XH=np.arange(0.0,AMax+dx,dx)
# ****** Elliptical **************
TissE=TisserandC(XE,T,"Elliptical")
ex1E=TisserandC(XE,T1,"Elliptical")
ex2E=TisserandC(XE,T2,"Elliptical")
ex3E=TisserandC(XE,T3,"Elliptical")
# ******** Hyperbolic ************
TissH=TisserandC(XH,T,"Hyperbolic")
ex1H=TisserandC(XH,T1,"Hyperbolic")
ex2H=TisserandC(XH,T2,"Hyperbolic")
ex3H=TisserandC(XH,T3,"Hyperbolic")
ex4H=TisserandC(XH,T4,"Hyperbolic")
ex5H=TisserandC(XH,T5,"Hyperbolic")
ex6H=TisserandC(XH,T6,"Hyperbolic")
ex7H=TisserandC(XH,T7,"Hyperbolic")


#===================================
#          LEGENDS ADN TEXTS
#===================================
LabelE=["$T=%.2f$"%T,"$T=%.2f$"%T1,"$T=%.2f$"%T2,"$T=%.2f$"%T3]
LabelH=["$T=%.2f$"%T,"$T=%.2f$"%T1,"$T=%.2f$"%T2,"$T=%.2f$"%T3,
        "$T=%.2f$"%T4,"$T=%.2f$"%T5,"$T=%.2f$"%T6,"$T=%.2f$"%T7]
TEXTE=r'$E=\sqrt{1-a_J\left(T-a_J/x\right)^2/4x}$'
TEXTH=r'$E=\sqrt{1+a_J\left(T-a_J/x\right)^2/4x}$'


#=======================================
#                PLOTS
#=======================================

"""
# ******* Elliptical ***********
fig1=plt.figure()
tissE=fig1.add_subplot(111)
tissE.plot(XE,TissE,'b-',label=LabelE[0])
tissE.plot(XE,ex1E,'r--',label=LabelE[1])
tissE.plot(XE,ex2E,'g--',label=LabelE[2])
tissE.plot(XE,ex3E,'m--',label=LabelE[3])
tissE.fill_between(XE,TissE,ex3E,where=ex3E>=TissE,color='red',alpha=0.2)
tissE.set_xlim(0,AMax)
tissE.set_ylim(0,1.0)
tissE.set_xlabel("Semimajor Axis (AU)")
tissE.set_ylabel("Eccentricity")
tissE.axvline(x=AJ,color='k',ls='--',lw=1.8)
tissE.set_xticks(np.arange(0,AMax+dT,2))
tissE.grid(True)
tissE.text(15.0,0.2,TEXTE,size=15,ha="center")
tissE.legend(loc='upper right')

# ********* Hyperbolical **********
fig2=plt.figure()
tissH=fig2.add_subplot(111)
tissH.plot(XH,TissH,'b-',label=LabelH[0])
tissH.plot(XH,ex1H,'r--',label=LabelH[1])
tissH.plot(XH,ex2H,'g--',label=LabelH[2])
tissH.plot(XH,ex3H,'m--',label=LabelH[3])
tissH.plot(XH,ex4H,'y--',label=LabelH[4])
tissH.plot(XH,ex5H,'c--',label=LabelH[5])
tissH.plot(XH,ex6H,'k--',label=LabelH[6])
tissH.plot(XH,ex7H,'r-.',label=LabelH[7])
#tissH.fill_between(XH,TissH,ex3H,where=ex3H>=TissH,color='blue',alpha=0.1)
tissH.set_xlim(0,10.0)
tissH.set_ylim(0,8.0)
tissH.set_xlabel("Semimajor Axis (AU)")
tissH.set_ylabel("Eccentricity")
tissH.grid(True)
tissH.text(5.0,4.0,TEXTH,size=15,ha="center")
tissH.legend(loc='upper right')
"""


#******************************
#    DYNAMICAL SECTIONS
#******************************

# ***** subregion ******
xs=np.arange(0,AMin,AMin/20.0)
ys=1.0*np.ones_like(xs)
x=np.r_[xs,XE]     # concatenate arrays
tiss=np.r_[ys,TissE]
#********* PLOT *********
fig3=plt.figure()
TissS=fig3.add_subplot(111)
TissS.plot(XE,TissE,'k-')
TissS.plot(XE,ex3E,'k-')
TissS.fill_between(XE,TissE,1.0, color = 'red', alpha=0.3)
#TissS.fill_between(XE,TissE,0.0,color = 'green', alpha=0.3)
TissS.fill_between(x,tiss,0.0,color = 'green', alpha=0.3)
TissS.set_ylim(0,1.0)
TissS.set_xlim(0,AMax)
plt.show()

