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
	python BIN/Building.py
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