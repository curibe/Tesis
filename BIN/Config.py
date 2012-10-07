#!/usr/bin/env python

'''
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# INITIAL PARAMETERS
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
'''

#======================
# TIME PARAMETERS
#======================
Time={
    'Unit':"days",
    'Start':0.0,
    'Elapsed':0.0,
    'End':0.0,
    'Step':-1E-2,
    'Output':0.5,
    'OutputElem':1.0,
    'Datadumps':10,    
    }

#=========================
# OBJECT PARAMETERS
#=========================
IO={'Name':'Io',
    'Mass':8.94E22,
    'Class':'SOLIDROCKY',
    'Type':'BIG'}

EUROPA={'Name':'Europa',
        'Mass':4.8E22,
        'Class':'SOLIDROCKY',
        'Type':'BIG'}

GANYMEDE={'Name':'Ganymede',
          'Mass':1.48E23,
          'Class':'SOLIDROCKY',
          'Type':'BIG'}

CALIXTO={'Name':'Calixto',
         'Mass':1.08E23,
         'Class':'SOLIDROCKY',
         'Type':'BIG'}

JUPITER={'Name':'Jupiter',
         'Mass':1.8985082106049875e+27,
         'Class':'GASGIANT',
         'Type':'BIG'}

SATURN={'Name':'Saturn',
        'Mass':5.668E26,
        'Class':'GASGIANT',
        'Type':'BIG'}

SUN={'Name':'SUN',
     'Mass':1.9884E30,
     'Class':'NORMALSTAR',
     'Type':'BIG'}


#=====================================
# OBJECTS INCLUDED IN THE SIMULATION
#=====================================
Bodyin=[
    'Io.pos',
    'Europa.pos',
    'Ganymede.pos',
    'Calixto.pos',
    'Saturn.pos',
    'Sun.pos'
    ]


##############################
# FILE NAME
##############################
'''
  Default: JupiterPos.dat
  location: Tesis/Cond_Iniciales
'''
File="StateInit.state"
