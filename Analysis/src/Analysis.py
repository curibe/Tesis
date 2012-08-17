import numpy as np
import matplotlib.pyplot as plt
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
AJ=778219200.0/AU

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



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#         FUNCTIONS
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


def Count_TvsA(vec):
    
    TmAm = TmAM = TMAm = TMAM = 0.0
    Nt=len(vec)
    for i in range(Nt):
        a=vec[i][0]
        T=vec[i][1]
        if T<=3 and a<=AJ: TmAm+=1
        if T<=3 and a>=AJ: TmAM+=1
        if T>=3 and a<=AJ: TMAm+=1
        if T>=3 and a>=AJ: TMAM+=1
        
    result=np.array([TmAm,TmAM,TMAm,TMAM])
    return result

def TisserandC(x,T,Type):
    
    if Type=="Elliptical":
        return np.sqrt(1-(AJ/(4*x))*(T-AJ/x)**2)
    if Type=="Hyperbolic":
        return np.sqrt(1+(AJ/(4*x))*(T-AJ/x)**2)


def TISSERAND(a,e,Type):
    if Type=="Elliptical":
        return AJ/a + 2*np.sqrt(a*(1-e**2)/AJ)
    if Type=="Hyperbolic":
        return AJ/a + 2*np.sqrt(a*(e**2-1)/AJ)
