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
	time python BIN/Building.py
	#BIN/./Build.out

Run:
	@echo "Running Simulation....."
	#python BIN/Running.py &>/dev/null
	python BIN/Running.py  
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
compile-builds:
	cd BIN/; g++ -lm -I. Build.cpp -o Build.out

#========================================
#   ANALYSIS RULES
#========================================

#****** Compiling ********
Analisis-compile:
	make  -C Analysis/src/ all
#****** Cleaning **********
Analisis-clean:
	make  -C Analysis/src/ clean

Analisis-Capture:
	@echo "Running Capture........\n"
	Analysis/src/CaptureT.out

Analisis-OrbFinal:
	Analysis/src/OE_Final_Jupiter.out

Analisis-END-SUN:
	Anlaysis/src/OE_END_SUN.out


#========================================
#   PLOT RULES
#========================================

Plot-Capture:
	python Analysis/src/PlotCaptureTime.py

Plot-CorrElm:
	python Analysis/src/Corr-Orbelms.py

Plot-OEDist:
	python Analysis/src/DistOrbElm.py



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