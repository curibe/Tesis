#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import os
import commands as cm
from math import *
from ICond import *


#==============
# SHORCUTS
#==============
system=os.system
get=cm.getoutput
getdir=os.getcwd
chdir=os.chdir

###########################
# END TIME
###########################
TF="19 FEB 2009 00:00:00.000"


Principal=getdir()
InitDir=Principal+"/Cond_Iniciales/"

#################################
# PREPARING INITIAL PARAMETERS:
# * Timeini.txt
# * State vector for each Body
#################################
chdir(InitDir)
cmd="./Cond_Ini.out '%s' %f"%(TF,dT)
system(cmd)

################################
# RUNNING 
################################
cmd="./CondIni_generator.py"
system(cmd)



