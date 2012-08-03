import numpy as np
import os
import commands as cm


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# UTIL CONSTANT
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
HOURS=3600.0
DAYS=24*HOURS
YEARS=365.25*DAYS
AU=1.49597870700e8 
RSOI=4.8305783e7
RJUP=71492.0


def BigBody(Body,State,ID,Flag):
    
    print>>Flag,"""\
#####################
#BODY %d
#####################
body(
Type=%s,
Code="BODY%d",
Name="%s",
Mass=%.4e,
ObjectClass=%s,
Density=0.0,
Radius=0.0,
Ep=EPOCH,
Frame="BODY0",
Units=ORBITAL,
State="%.15e %.15e %.15e %.15e %.15e %.15e",
As="a1=0.0 a2=0.0 a3=0.0", 
Spin="0.0 0.0 0.0",
CloseEncounter=1E-4,
ShowObject=1,
Activate=1,
),#COMA MANDATORY"""%(ID,Body['Type'],ID,Body['Name'],Body['Mass'],Body['Class'],
     State[0],State[1],State[2],State[3],State[4],State[5])


def CentralBody(Body,Flag):

    print>>Flag,"""\
#####################
#BODY 0:
#####################
body(
Type=CENTRAL,
Code="BODY0",
Name="%s",
Mass=1.0*%s,
ObjectClass=%s,
Density=0.0,
Radius=0.0,
Frame="BODY0",
Units=ORBITAL,
Ep=EPOCH,
State="0.0 0.0 0.0 0.0 0.0 0.0",
Cartesian=np.array([0.0,0.0,0.0,0.0,0.0,0.0]),
J2=0.0,J4=0.0,J6=0.0,
CloseEncounter=1.0,
ShowObject=1,
Activate=1,
),#COMMA MANDATORY"""%(Body['Name'],Body['Mass'],Body['Class'])


def MinorBody(ID,State,Flag):
    
    print>>Flag,"""\
#####################
#BODY %d
#####################
body(
Type=SMALL,
Code="BODY%d",
Name="Comet",
Mass=1E-3*MMOON,
ObjectClass=ICEPLSIMAL,
Density=0.0,
Radius=0.0,
Ep=EPOCH,
Frame="BODY0",
Units=ORBITAL,
State="%.15e %.15e %.15e %.15e %.15e %.15e",
As="a1=0.0 a2=0.0 a3=0.0", 
Spin="0.0 0.0 0.0",
CloseEncounter=1E-4,
ShowObject=1,
Activate=1,
),#COMA MANDATORY"""%(ID,ID,State[0],State[1],State[2],State[3],State[4],State[5])


def HeadConfig(time,ID,Flag,index):

    unit=time['Unit']
    unit=unit.upper()
    deltaT=(time['End']-time['Start'][index])/eval(unit)
    print>>Flag,"""\
from mercupy import *
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#DESCRIPTION
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
DOCSTRING=\\
'''
This Configuration file corresponding to run %d
'''

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#GLOBAL PROPERTIES OF INTEGRATION
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#01/01/2012 00:00:00.000
EPOCH=0.0

TIME_UNIT="%s"
TIME_START=0.0
TIME_ELAPSED=%g
TIME_STOP=TIME_START+TIME_ELAPSED
TIME_STEP=%e

DT_OUTPUT=%g
DT_OUTPUTELEM=%g
DT_DATADUMPS=%g

COORDINATES[CENTRAL]="Cartesian"
COORDINATES[BIG]="Cartesian"
COORDINATES[SMALL]="Cartesian"

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#BODIES
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
BODIES=["""%(ID,time['Unit'],deltaT,
             time['Step'],time['Output'],time['OutputElem'],time['Datadumps'])



def TailConfig(Flag):

    print>>Flag,"""\
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#END BODIES
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
]#THIS LINE IS MANDATORY

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#OUTPUT ELEMENTS
#Format: XN[.M|e]
#Where: X:element letter,N:reserved spaces,M:decimal
#       places,e:scientific notation
#Available: 
#  x,y,z:position;u,v,w:velocity
#  a,e,i:classical elements
#  g:periapsis argument,n:long.asc.node,l:mean anom
#  r:radial dist.,q: peric.,b:apoc.(Q),p:long.per.,f:true anom.
#  s:spin period, d:density, m:mass
#  R:Radius(km), P:Period(years), E:Central Energy, L:Central Angular Momentum
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
POSITION_ELEMENTS="x15e y15e z15e u15e v15e w15e r15e"
ORBITAL_ELEMENTS="a15e e15e i15e g15e n15e l15e q15e b15e p15e f15e"
PHYSICAL_ELEMENTS="s8.5 o8.5 m10e d8.5"
ADDITIONAL_ELEMENTS="R15e P15e E15e L15e"
OUTPUT_FORMAT="%-15.10e"

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#GENERAL BEHAVIOR OF THE INTEGRATOR
#Modify only if you know what are you doing
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#STOP INTEGRATION AFTER A CLOSE ENCOUNTER
STOPINTEG="no"
#ALLOW COLLISIONS TO OCCUR
COLLISIONS="no"
#INCLUDE COLLISIONAL FRAGMENTATION
FRAGMENTATION="no"
#ALGORITHM (MVS, BS, BS2, RADAU, HYBRID ETC)
INTEGRATION_ALGORITHM="BS"
#ACCURACY
INTEGRATION_ACCURACY=1E-12
#OUTPUT PRECISION = MEDIUM
INTEGRATION_PRECISION="medium"
#HYBRID INTEGRATOR CHANGEOVER (HILL RADII) = 3.
INTEGRATION_CHANGEOVER=3.0
#REFERENCE FRAME FOR OUTPUT ELEMENTS: CENTRAL, BARYCENTRIC, JACOBI
OUT_ELEMENTS="Central"
#NUMBER OF TIMESTEPS BETWEEN PERIODIC EFFECTS 
DSTEP_PERIODIC=100
#EXPRESS TIME RELATIVE TO INTEGRATION START TIME
TIME_RESPINTEGRATION="yes" """


def loadDesc(filename):
    D=dict()
    execfile(filename,{},D)
    return D
'''
def dic2list(DIC):
    L=DIC.keys()
    V=DIC.values()
    List=[]
    #for i in xrange(len(L)):
    #     vars()(L[i])=V[i]
    for i in xrange(len(L)):
        List.append(L[i])

    return List
'''


def Description(time,index):

    unit=time['Unit']
    unit=unit.upper()
    ofile=open("Description.txt","w")
    ofile.write("""\
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#DESCRIPTION
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# This Directory contain the results of run %d.
# The parameters related with these run are:

#===============================================
#TIME PARAMETERS
#===============================================

#***************************
# Time Unit: 
#***************************
Unit = "%s"

#***************************
# Time Start: 
#***************************
Start = %f
#Tini = %e   # seconds

#***************************
# Time End:
#***************************
End = %f
#Tend = %e  # seconds

#*******************
# Time Output: 
#*******************
Output = %.2f

#*********************
# Time OutputElem:
#*********************
OutElm = %.2f

#*********************
# Time Datadumps:  
#*********************
DataDumps = %.2f
"""%(index+1,time['Unit'],time['Start'][index]/eval(unit),time['Start'][index],
     time['End']/eval(unit),time['End'],time['Output'],time['OutputElem'],time['Datadumps']))
    ofile.close()



