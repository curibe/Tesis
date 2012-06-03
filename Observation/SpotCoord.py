#!/usr/bin/python

from math import *
import numpy as np

def SpotC(DeltaY,DeltaZ,R):
    
    DeltaX=sqrt(R**2-DeltaY**2-DeltaZ**2)
    Phi=np.arctan(DeltaY/DeltaX)
    Theta=np.arccos(DeltaZ/R)

    print "*"*40
    print "PARAMETROS UTILIZADOS Y ANGULOS DE LA MANCHA"
    print "*"*40
    print "RADIO DE LA ESFERA:  "+str(R)+" cm"
    print "DX:  "+str(DeltaX)+" cm"
    print "DY:  "+str(DeltaY)+" cm"
    print "DX:  "+str(DeltaZ)+" cm"
    print "Theta: "+str(Theta*180/pi)+" deg"
    print "Phi: "+str(Phi*180/pi)+" deg"
    print "*"*40
    
