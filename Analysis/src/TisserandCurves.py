import numpy as np
import matplotlib.pyplot as plt
import os
import commands as cm
from Analysis import *

#==============================
#          PARAMETERS
#==============================
dT=0.1
dx=0.01
AMin=1.734
AMax=20.0
AMin3=2.604
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
tissH.set_xlim(0,10.0)
tissH.set_ylim(0,8.0)
tissH.set_xlabel("Semimajor Axis (AU)")
tissH.set_ylabel("Eccentricity")
tissH.grid(True)
tissH.text(5.0,4.0,TEXTH,size=15,ha="center")
tissH.legend(loc='upper right')


#******************************
#    DYNAMICAL SECTIONS
#******************************

# ***** subregion ******
Ex3E=TisserandC(X3E,T3,"Elliptical")
xs=np.arange(0,AMin,AMin/20.0)
ys=1.0*np.ones_like(xs)
#*********************
tmp=np.ones_like(XE)*AMin3
idx=float(np.where(np.fabs(XE-tmp)<=1.0e-05)[0])
xs2=XE[:idx]
ys2=np.ones_like(xs2)
#**********************
x=np.r_[xs,XE]     # concatenate arrays
tiss=np.r_[ys,TissE]
x2=np.r_[xs2,X3E]
EX3E=np.r_[ys2,Ex3E]
#********* PLOT *********
fig3=plt.figure()
TissS=fig3.add_subplot(111)
TissS.plot(XE,TissE,'k-')
TissS.plot(X3E,Ex3E,'k-')
TissS.fill_between(X3E,Ex3E,1.0, color = 'blue', alpha=0.2)
TissS.fill_between(x2,TissE,EX3E,where=TissE<EX3E, color = 'red', alpha=0.2)
TissS.fill_between(x,tiss,0.0,color = 'green', alpha=0.2)
TissS.set_ylim(0,1.0)
TissS.set_xlim(0,AMax)
TissS.set_xlabel("Semimajor Axis (AU)")
TissS.set_ylabel("Eccentricity")
#******* Text JFC **********
TissS.text(8.0,0.7,"Jupiter Family Comets",size=14,ha="center",fontweight='bold')
TissS.text(8.0,0.65,"Short Period Comets",size=14,ha="center",fontweight='bold')
TissS.text(8.0,0.6,"2.0<T<3.0",size=14,ha="center",fontweight='bold')
#******* Long Period Comets ********
TissS.text(10.0,0.93,"Oort Cloud's objects (LPC)",size=14,ha="center",fontweight='bold')
TissS.text(10.0,0.88,"T<2.0",size=14,ha="center",fontweight='bold')
#********** Ateroids *************
TissS.text(14.0,0.3,"Asteroids",size=14,ha="center",fontweight='bold')
TissS.text(14.0,0.23,"T>3.0",size=14,ha="center",fontweight='bold')
TissS.text(1.8,0.3,"Asteroids",size=14,ha="center",fontweight='bold')
TissS.text(1.8,0.23,"T>3.0",size=14,ha="center",fontweight='bold')
TissS.grid(True)

plt.show()

