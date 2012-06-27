#!/usr/bin/python

import numpy as np
from numpy import linalg as LA
from math import *
from ICond import *

############################
# Algunas Funciones
############################
mag=lambda x:sqrt(np.dot(x,x))
RAD2DEG=lambda x:x*180.0/pi
DEG2RAD=lambda x:x*pi/180.0

###################################
# Angulos esfericos de la mancha
###################################
#Theta0=(180-34)*pi/180.0
#Phi0= (360-38)*pi/180.0

# Variables que se necesitan:
# omega, et_obs,Rprom,beta


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Rotation Coordinates 2D
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%
def Rotation(X,theta,mode):
    cos=np.cos
    sin=np.sin
    if mode=='counterclockwise':
        xr = X[0]*cos(theta) - X[1]*sin(theta)
        yr = X[0]*sin(theta) + X[1]*cos(theta)
    if mode=='clockwise':
        xr = X[0]*cos(theta) + X[1]*sin(theta)
        yr = -X[0]*sin(theta) + X[1]*cos(theta)
    
    return np.array([xr,yr])




########################################
# MODULO QUE PASA DEL STMA DE VELOCIDAD
# AL SISTEMA AXIAL
########################################
def rotationVel(xo,theta,phi):

    t1=np.cos(phi)*np.cos(theta)
    t2=-np.sin(phi)
    t3=np.sin(theta)*np.cos(phi)
    t4=np.sin(phi)*np.cos(theta)
    t5=np.cos(phi)
    t6=np.sin(theta)*np.sin(phi)
    t7=-np.sin(theta)
    t8=0.0
    t9=np.cos(theta)

    xf=np.zeros(3)
    xf[0]=t1*xo[0] + t2*xo[1] + t3*xo[2]
    xf[1]=t4*xo[0] + t5*xo[1] + t6*xo[2]
    xf[2]=t7*xo[0] + t8*xo[1] + t9*xo[2]

    return xf


###############################
# 
###############################
def Phi_Calculate(t,et_obs):

    XM=np.zeros(3)

    #Necesito el valor de et_obs. Hacer un archivo de configuracion.
    phi=Phi0+omega*(t-et_obs)
    #print "In Phi calculate..... Phi: "+str(RAD2DEG(phi))+"   Phi0: "+str(RAD2DEG(Phi0))

    # En el SR Axial
    XA=Req*np.sin(Theta0)*np.cos(phi)
    YA=Req*np.sin(Theta0)*np.sin(phi)
    ZA=Req*np.cos(Theta0)

    # En el SR de la imagen
    XM[0]=XA
    XM[1]=YA*np.cos(beta)+ZA*np.sin(beta)
    XM[2]=-YA*np.sin(beta)+ZA*np.cos(beta)
    RA=[XA,YA,ZA]

    #return XM,RA
    return XM

##############################################
# FUNCION QUE GRAFICA LOS STMAS DE REFERENCIA
# EL VECTOR POSICION Y EL VECTOR VELOCIDAD
##############################################
#def gnuplot_refS(UI,XI,VE):

#################################
# SHOW INFORMATION
#################################
def ShowInformation(xmA,xmI,xmE,VA,VEL,vE):
    print "*"*60
    print "PARAMETROS DE SALIDA"
    print "*"*60+"\n"
    print "* COORDENADAS DE LA MANCHA:\n"
    print "    SISTEMA AXIAL:"
    print "    -----------------------------"
    print "    XI: %10g   YI: %10g  ZI: %10g \n"%(xmA[0],xmA[1],xmA[2])
    print "    SISTEMA DE LA IMAGEN:"
    print "    -----------------------------"
    print "    XI: %10g   YI: %10g  ZI: %10g \n"%(xmI[0],xmI[1],xmI[2])
    print "    SISTEMA ECLIPTICO:"
    print "    -----------------------------"
    print "    XE: %10g   YE: %10g  ZE: %10g \n"%(xmE[0],xmE[1],xmE[2])
    print "|xmI|: "+str(mag(xmI))+ "  |xmE|: "+str(mag(xmE))+"\n"
    print "* VELOCIDAD:\n"
    print "    SISTEMA AXIAL: "
    print "    -----------------------------"
    print "    VAx: %10g  VAy: %10g  VAz: %10g \n"%(VA[0],VA[1],VA[2])
    print "    SISTEMA DE LA IMAGEN: "
    print "    -----------------------------"
    print "    VELx: %10g  VELy: %10g  VELz: %10g \n"%(VEL[0],VEL[1],VEL[2])
    print "    SISTEMA ECLIPTICO: "
    print "    -----------------------------"
    print "    vEx: %10g  vEy: %10g  vEz: %10g \n"%(vE[0],vE[1],vE[2])
    print "    -----------------------------"
    print "    MAGNITUDES:"
    print "    -----------------------------"
    print "    |VA|: "+str(mag(VA))+"  |VEL|: "+str(mag(VEL))+"   |vE|: "+str(mag(vE))+"\n"
    print "*"*60
    



def Plot(XI,Xm,XA,Xv,V):
    
    XVF=np.zeros(3)
    YVF=np.zeros(3)
    ZVF=np.zeros(3)
    Vel=np.zeros(3)
    xm=Xm/mag(Xm)
    XVF[0] = xm[0] + Xv[0][0]*0.5
    XVF[1] = xm[1] + Xv[0][1]*0.5
    XVF[2] = xm[2] + Xv[0][2]*0.5
    YVF[0] = xm[0] + Xv[1][0]*0.5
    YVF[1] = xm[1] + Xv[1][1]*0.5
    YVF[2] = xm[2] + Xv[1][2]*0.5
    ZVF[0] = xm[0] + Xv[2][0]*0.5
    ZVF[1] = xm[1] + Xv[2][1]*0.5
    ZVF[2] = xm[2] + Xv[2][2]*0.5
    Vel[0] = xm[0] - V[0]*0.5
    Vel[1] = xm[1] - V[1]*0.5
    Vel[2] = xm[2] - V[2]*0.5
    print "Vel: ", Vel[0],Vel[1],Vel[2]
    print "V: ", V[0],V[1],V[2]
    print "Xm: ",xm[0],xm[1],xm[2]
    ofile=open("Axis.gpl","w")
    ofile.write("""\
reset
R=%.1f
unset arrow
unset label
set xyplane 0.0
set size square
set arrow from 0.0,0.0,0.0 to 1.0,0.0,0.0  lw 1.5
set arrow from 0.0,0.0,0.0 to 0.0,1.0,0.0  lw 1.5
set arrow from 0.0,0.0,0.0 to 0.0,0.0,1.0  lw 1.5

set label at 1.1,0.0,0.0 'Xecl' 
set label at 0.0,1.1,0.0 'Yecl' 
set label at 0.0,0.0,1.1 'Zecl' 

set arrow from 0.0,0.0,0.0 to %f,%f,%f ls 4 lw 1.5
set arrow from 0.0,0.0,0.0 to %f,%f,%f ls 4 lw 1.5
set arrow from 0.0,0.0,0.0 to %f,%f,%f ls 4 lw 1.5

set label at %f,%f,%f 'XI' tc lt 4 
set label at %f,%f,%f 'yI' tc lt 4 
set label at %f,%f,%f 'ZI' tc lt 4 

set arrow from 0.0,0.0,0.0 to %f,%f,%f ls 3 lw 1.5
set arrow from 0.0,0.0,0.0 to %f,%f,%f ls 3 lw 1.5
set arrow from 0.0,0.0,0.0 to %f,%f,%f ls 3 lw 1.5

set label at %f,%f,%f 'XA' tc lt 3 
set label at %f,%f,%f 'XA' tc lt 3 
set label at %f,%f,%f 'XA' tc lt 3 

set arrow from 0.0,0.0,0.0 to %f,%f,%f ls 5 lw 1.5

set arrow from %f,%f,%f to %f,%f,%f ls 7 lw 1.5
set arrow from %f,%f,%f to %f,%f,%f ls 7 lw 1.5
set arrow from %f,%f,%f to %f,%f,%f ls 7 lw 1.5

set arrow from %f,%f,%f to %f,%f,%f ls 8 lw 1.5

set parametric
set isosample 30,30
set xlabel 'XECL'
set ylabel 'YECL'
set zlabel 'ZECL'
splot cos(u)*sin(v),sin(u)*sin(v),cos(v) notitle  w d
"""%(Req,XI[0][0],XI[0][1],XI[0][2],
     XI[1][0],XI[1][1],XI[1][2],
     XI[2][0],XI[2][1],XI[2][2],
     1.2*XI[0][0],1.2*XI[0][1],1.2*XI[0][2],
     1.2*XI[1][0],1.2*XI[1][1],1.2*XI[1][2],
     1.2*XI[2][0],1.2*XI[2][1],1.2*XI[2][2],
     XA[0][0],XA[0][1],XA[0][2],
     XA[1][0],XA[1][1],XA[1][2],
     XA[2][0],XA[2][1],XA[2][2],
     1.05*XA[0][0],1.05*XA[0][1],1.05*XA[0][2],
     1.2*XA[1][0],1.2*XA[1][1],1.2*XA[1][2],
     1.2*XA[2][0],1.2*XA[2][1],1.2*XA[2][2],     
     Xm[0]/mag(Xm),Xm[1]/mag(Xm),Xm[2]/mag(Xm),
     xm[0],xm[1],xm[2],XVF[0],XVF[1],XVF[2],
     xm[0],xm[1],xm[2],YVF[0],YVF[1],YVF[2],
     xm[0],xm[1],xm[2],ZVF[0],ZVF[1],ZVF[2],
     Vel[0],Vel[1],Vel[2],xm[0],xm[1],xm[2]))
    ofile.close()

    print xm[0],xm[1],xm[2],Vel[0],Vel[1],Vel[2]


##########################################
# FUNCION QUE PASA DEL STMA DE REFERENCIA
# DE JUPITER (IMAGEN) AL SR ECLIPTICO
##########################################
def SRI2ECL(t,RJE,XJ,Vimp):
    '''
    ****************************************
     Se hace un proceso de Gram-Schmidt
     Se hallan los vectores unitarios del SR de la imagen
     en terminos del SR Ecliptico
    ****************************************
    '''
    UIx=RJE/mag(RJE)   #RJE es el radio vector Tierra-jupiter
    UZ=np.array([0,0,1])
    proj=np.dot(UZ,UIx)/np.dot(UIx,UIx)
    UIz=UZ-proj*UIx
    UIy=np.cross(UIz,UIx)
    UIz=UIz/mag(UIz)
    UIy=UIy/mag(UIy)

    angle1=np.arcsin(RJE[2]/mag(RJE))
    angle2=np.arcsin(UIx[2])
    '''
    print "%"*30
    print "Xj: %e   Yj: %e   Zj: %e"%(RJE[0],RJE[1],RJE[2])
    print "UIx[0]: %f  UIx[1]: %f   UIx[2]: %f"%(UIx[0],UIx[1],UIx[2])
    print "The Angle between Jupiter and Earth is: "
    print "Unitary Vector: %f     RadioVector: %f"%(RAD2DEG(angle2),RAD2DEG(angle1))
    
    print "\n===== EJES DEL STMA IMAGEN========"
    print "UIx[0]: %g  UIx[1]: %g   UIx[2]: %g"%(UIx[0],UIx[1],UIx[2])
    print "UIy[0]: %g  UIy[1]: %g   UIy[2]: %g"%(UIy[0],UIy[1],UIy[2])
    print "UIz[0]: %g  UIz[1]: %g   UIz[2]: %g"%(UIz[0],UIz[1],UIz[2])
    print "mag(UIx): "+str(mag(UIx))+"  mag(UIy): "+str(mag(UIy))+"  mag(UIz): "+str(mag(UIz))
    print "RJEx: %g   RJEy: %g    RJEz: %g"%(RJE[0],RJE[1],RJE[2])
    print "="*30
    '''
    '''
    ***********************************
    Se calculan las coordenadas de la Mancha
    en el SR Ecliptico
    ***********************************
    '''

    XmE=np.zeros(3)

    XmE[0]=XJ[0]*UIx[0] + XJ[1]*UIy[0] + XJ[2]*UIz[0]
    XmE[1]=XJ[0]*UIx[1] + XJ[1]*UIy[1] + XJ[2]*UIz[1]
    XmE[2]=XJ[0]*UIx[2] + XJ[1]*UIy[2] + XJ[2]*UIz[2]
    #XmE[0]=XJ[0]*UIx[0]
    #XmE[1]=0.0
    #XmE[2]=0.0
    
    #==================================================
    # Se calcula la velocidad en el SR Ecliptico
    #==================================================
    v=np.zeros(3)
    #v[0]=-Vimp*np.sin(0.0)*np.cos(0.0)
    #v[1]=-Vimp*np.sin(0.0)*np.sin(0.0)
    #v[2]=-Vimp*np.cos(0.0)
    v[0]=-Vimp*np.sin(AlphaV)*np.cos(PhiV)
    v[1]=-Vimp*np.sin(AlphaV)*np.sin(PhiV)
    v[2]=-Vimp*np.cos(AlphaV)
    
    # print "Stma Velocidad: "
    # print v
    # print"\n"
    # print"%%"*15
    Phi=Phi0+omega*(t-ET_obs)

    # Se pasa del SR de la Velocidad (Tangente a Jupiter) al 
    # sistema axial
    VelAxial=rotationVel(v,Theta0,Phi)
 
    # Se pasa del sistema axial al sistema de la Imagen
    Vel=np.zeros(3)
    Vel[0]=VelAxial[0]
    Vel[1]=VelAxial[1]*np.cos(beta)+VelAxial[2]*np.sin(beta)
    Vel[2]=-VelAxial[1]*np.sin(beta)+VelAxial[2]*np.cos(beta)

    # Se pasa del SR de la Imagen al SR Ecliptico
    Vecl=np.zeros(3)
    Vecl[0]=Vel[0]*UIx[0] + Vel[1]*UIy[0] + Vel[2]*UIz[0]
    Vecl[1]=Vel[0]*UIx[1] + Vel[1]*UIy[1] + Vel[2]*UIz[1]
    Vecl[2]=Vel[0]*UIx[2] + Vel[1]*UIy[2] + Vel[2]*UIz[2]
    
    
    #print " et: %e    xe: %e   ye: %e   ze: %e    vxe: %e    vye: %e   vze: %e"%(t,XmE[0],XmE[1],XmE[2],Vecl[0],Vecl[1],Vecl[2])    
    #print " et: %e r: %f  v: %f"%(t,mag(XmE),mag(Vecl))
    '''
    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    # PLOTS OF REFERENCE FRAMES
    #%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    #Se determinan los ejes del sistema de Referencia de la velocidad
    # Ejes del SR de la velocidad
    Xv=np.zeros(3);  Yv=np.zeros(3);  Zv=np.zeros(3);
    Xv[0]=1.0/2.0;	Xv[1]=Xv[2]=0.0;
    Yv[1]=1.0/2.0;	Yv[0]=Yv[2]=0.0;
    Zv[2]=1.0/2.0;	Zv[0]=Zv[1]=0.0;
    # Se pasa del SR de la Velocidad al SR de la Imagen
    # mediante una rotacion
    XIv=rotationVel(Xv,Theta0,Phi)
    YIv=rotationVel(Yv,Theta0,Phi)
    ZIv=rotationVel(Zv,Theta0,Phi)
    # Se pasa del SRI al SR Ecliptico
    XJv=np.zeros(3);   YJv=np.zeros(3);    ZJv=np.zeros(3);
    XJv[0]=XIv[0]*UIx[0] + XIv[1]*UIy[0] + XIv[2]*UIz[0]
    XJv[1]=XIv[0]*UIx[1] + XIv[1]*UIy[1] + XIv[2]*UIz[1]
    XJv[2]=XIv[0]*UIx[2] + XIv[1]*UIy[2] + XIv[2]*UIz[2]
    
    YJv[0]=YIv[0]*UIx[0] + YIv[1]*UIy[0] + YIv[2]*UIz[0]
    YJv[1]=YIv[0]*UIx[1] + YIv[1]*UIy[1] + YIv[2]*UIz[1]
    YJv[2]=YIv[0]*UIx[2] + YIv[1]*UIy[2] + YIv[2]*UIz[2]
    
    ZJv[0]=ZIv[0]*UIx[0] + ZIv[1]*UIy[0] + ZIv[2]*UIz[0]
    ZJv[1]=ZIv[0]*UIx[1] + ZIv[1]*UIy[1] + ZIv[2]*UIz[1]
    ZJv[2]=ZIv[0]*UIx[2] + ZIv[1]*UIy[2] + ZIv[2]*UIz[2]

    UnV=np.array([XJv/mag(XJv),YJv/mag(YJv),ZJv/mag(ZJv)])

    # Se dibujan los Ejes coordenados
    UnI=np.array([UIx,UIy,UIz])
     # En el SR Axial
    XA=Req*np.sin(0.0)*np.cos(np.pi/2.0)
    YA=Req*np.sin(0.0)*np.sin(pi/2.0)
    ZA=Req*np.cos(0.0)
    # En el SR de la imagen
    XM=np.zeros(3)
    XM[0]=XA
    XM[1]=YA*np.cos(beta)+ZA*np.sin(beta)
    XM[2]=-YA*np.sin(beta)+ZA*np.cos(beta)
    zA=np.zeros(3)
    zA[0]=XM[0]*UIx[0] + XM[1]*UIy[0] + XM[2]*UIz[0]
    zA[1]=XM[0]*UIx[1] + XM[1]*UIy[1] + XM[2]*UIz[1]
    zA[2]=XM[0]*UIx[2] + XM[1]*UIy[2] + XM[2]*UIz[2]
    UAy=np.cross(zA/mag(zA),UIx)
    UAXIAL=np.array([UIx,UAy,zA/mag(zA)])

    UvZ=XmE/mag(XmE)   #RJE es el radio vector Tierra-jupiter
    UZ=np.array([0,0,1])
    proj=np.dot(UZ,UvZ)/np.dot(UvZ,UvZ)
    UvX=UZ-proj*UvZ
    UvY=np.cross(UvZ,UvX)
    #UIz=UIz/mag(UIz)
    #UIy=UIy/mag(UIy)
    UV=np.array([-UvX,-UvY,UvZ])

    Plot(UnI,XmE,UAXIAL,UV,Vecl/mag(Vecl))
    '''

    return XmE, Vecl#, VelAxial,Vel
    #return XmE, Vecl, VelAxial,Vel


'''
X=np.loadtxt("IniProbe.txt")
et=X[0]
Xje=X[1:]

xmI,xmA=Phi_Calculate(et,ET_obs)
xmE,vE,VA,VEL= SRI2ECL(et,Xje,xmI,Vmin)

ShowInformation(xmA,xmI,xmE,VA,VEL,vE)
'''





#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#  MAIN PROGRAM
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

icond = open("StateInit.state","w")
X=np.loadtxt("JupiterPos.dat")
et=X[0:,0]
XJe=X[:,1:4]
i=0
#for Timp in et:
for Vimp in np.arange(Vmin,Vmax+0.5*dV,dV):
    i=0
    for Timp in et:
        xmI = Phi_Calculate(Timp,ET_obs)
        xmE,vE= SRI2ECL(Timp,XJe[i],xmI,Vimp)
        #vmag=sqrt(vE[0]**2+vE[1]**2+vE[2]**2)
        #print "j: ",j,"  Vimp: ",Vimp
        #j=j+1
        icond.write("%.15e  %.15e  %.15e  %.15e  %.15e  %.15e %.15e %.15e %.3f\n"%(Timp,xmE[0],xmE[1],xmE[2],vE[0],vE[1],vE[2],mag(xmE),mag(vE)))
        i = i+1
        #print "Timp: %.15e    i=%d\n"%(Timp,i)
    #i = i+1

icond.close()


