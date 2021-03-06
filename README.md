####################################################
# 
#
#
####################################################

This code uses Mercupy, a wrapper of Mercury package, design by Jorge Zuluaga. 
The Mercury package was developed by John Chambers.
This programs has been designed to solve the impact event on Jupiter in July 2009
The code have the follow structure:


INITIAL CONDITIONS
=====================
In this section, the code generate the initial condition of impact 
(impact location and impact velocity),following certain parameter 
established. In order to generate the initial condition, following 
programs or steps has been executed in this order:

1. ICond.py
   This is the configuration file. The initial parameters are 
   established: Impact velocity, impact time,Impact Loaction(Latitude 
   and longitude). Step size for Time and velocity.

2. InitialCond.py
   This program execute other programs which generate the data file 
   for each body in the simulation, according to the time,position 
   and velocity of impact established. 
   The programs that are executed are:
			
   2.1 Cond_Ini.cpp : Generate data file with the state of each body 
   in the simulation for different values of the impact time. This 
   program generate a text file with time values converted to 
   Julian Date JD2000. 
   ANNOTATION: if the temporal step size going to be changed, remember 
   that the step size is set manually in this program.

   2.2 CondIni_generator: This program convert the initial condition 
   given in the Jupicentric system to Ecliptic system, creating a 
   output file "StateIni.state" with the time, position and velocity 
   of impactor object respect to Ecliptic system or ECLIPJ2000. 
   The program read a file "JupiterPos.dat" created by Cond_Ini.cpp

   ANNOTATION: The time_stop of the integration (final date) is 
   established in InitialCond.py, therefore, if the Time_Stop 
   going to be modified, this must be done in this program.
