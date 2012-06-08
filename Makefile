##############################
# Makefile 
##############################



############################
# RULES
############################

Init:
	echo "Initialiting Simulation...."
	python BIN/Init.py

Building:
	echo "Building Simulation....."
	python BIN/Building.py

Run:
	echo "Running Simulation....."
	$(shell\
	if [ -z "$1"]; \
	then python BIN/Running.py $(N)
	else python BIN/Running.py;\
	 fi)
Ref:
	python BIN/RefChange.py

Probe:
	python BIN/Probe.py $(argv)
