##############################
# Makefile 
##############################

SHELL=/bin/bash

############################
# RULES
############################

Init:
	@echo "Initialiting Simulation...."
	python BIN/Init.py

Building:
	@echo "Building Simulation....."
	#time python BIN/Building.py
	time BIN/./Build.out

Run:
	@echo "Running Simulation....."
	#python BIN/Running.py &>/dev/null
	time python BIN/Running.py  
Ref:
	python BIN/RefChange.py

Probe:
	python BIN/Probe.py $(argv)

Capture:
	python BIN/TimeCapture.py

condini:
	python Cond_Iniciales/InitialCond.py

utilprog:
	make -s -C UTILPROG all install



#============================
# COMPILING FILES
#============================

compile-all:mercupy-compile bin-compile condini-compile utilprog condini
	@echo "*************************************************"
	@echo "Compiling all...."
	@echo "Compiling folder : Mercupy .....DONE"
	@echo "Compiling  Build .....DONE"
	@echo "Compiling folder : Cond_Iniciales .....DONE"
	@echo "Compiling folder : UTILPROG .....DONE"
	@echo "Running Cond_Iniciales .... DONE"
	@echo "Copying File ICond.py in BIN ..... DONE"
	@echo "**************************************************"

bin-compile:
	cd BIN/; g++ -Wall -lm -I. Build.cpp -o Build.out

condini-compile:
	make -s -C Cond_Iniciales all
	cp Cond_Iniciales/ICond.py BIN/

mercupy-compile:
	make -s -C MercuPy clean prepare build



#========================================
#   ANALYSIS RULES
#========================================

#****** Compiling ********
Analisis-compile:
	make -s -C Analysis/src/ all
#****** Cleaning **********
Analisis-clean:
	make -s -C Analysis/src/ clean
	cd Analysis/; rm -rf *.orb *.dat *.txt 

Analisis-Capture:
	@echo "Running Capture........\n"
	Analysis/src/./CaptureT.out

Analisis-OrbFinal:
	Analysis/src/./OE_Final_Jupiter.out

Analisis-END-SUN:
	Analysis/src/./OE_END_SUN.out

Analisis-EQcoord:
	Analysis/src/./EQCoord.out


#========================================
#   PLOT RULES
#========================================

Plot-Capture:
	python Analysis/src/PlotCaptureTime.py

Plot-CorrElm:
	python Analysis/src/Corr-Orbelms.py

Plot-OEDist:
	python Analysis/src/DistOrbElm.py

Plot-Heatmap:
	python Analysis/src/HeatMap.py



#==============================
#   CLEAN FILES
#==============================

clean-all:utilprog-clean condini-clean bin-clean Analisis-clean
	@echo "********************************************"
	@echo "Cleaning all files...."
	@echo "Cleaning folder : UTILPROG ....DONE"
	@echo "Cleaning folder : Cond_Iniciales ....DONE"
	@echo "Cleaning folder : BIN ....DONE"
	@echo "Cleaning folder : Analysis ....DONE"
	@echo "********************************************"

utilprog-clean:
	make -s -C UTILPROG clean

condini-clean:
	make -s -C Cond_Iniciales clean

bin-clean:
	cd BIN/; rm *.out *~ *.pyc

mercupy-clean:
	make  -C MercuPy clean



#=============
# TRASH
#=============
cp-prog:
	cp Analysis/src/OrbElm_Jup2Sun.out RUNDIR/run240/

####################################
# EMACS SESSIONS
####################################
ICONDPATH=Cond_Iniciales
BINPATH=BIN
ICONDFILES=$(ICONDPATH)/CondIni_generator.py $(ICONDPATH)/ICond.py $(ICONDPATH)/InitialCond.py
BINFILES=$(BINPATH)/Init.py $(BINPATH)/Building.py $(BINPATH)/Config.py $(BINPATH)/Jupiter.py $(BINPATH)/Running.py

inicond:
	emacs $(ICONDFILES) &

bin:
	emacs $(BINFILES) &