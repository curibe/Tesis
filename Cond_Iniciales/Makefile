CC = g++

LFLAGS= -L/usr/lib -lgsl -lgslcblas /usr/local/Orbital/cspice/lib/cspice.a /usr/local/Orbital/cspice/lib/csupport.a -lm  -L/usr/local/Orbital/gfortran/lib -lpthread -ldl  -lgcc_s
#/usr/local/Orbital/ipopt/lib/libipopt.a
CFLAGS=  -c -Wall -O4 -I. -I/usr/include -I/usr/local/Orbital/cspice/include  -I/usr/local/Orbital/gsl/include/gsl -I/usr/local/Orbital/PIgsl/include  -I/usr/local/Orbital/include

#-I/usr/local/Orbital/ipopt/include -I/usr/local/Orbital/ipopt/include/coin

# CC = gcc
#CSPICEDIR = /usr/local
#CFLAGS = -g -c -Wall  -I$(CSPICEDIR)/include/cspice
#LFLAGS =-lm -lgsl -lgslcblas $(CSPICEDIR)/lib/cspice.a $(CSPICEDIR)/lib/csupport.a


EXE = Cond_Ini
# EXE= JupiterSpice

all: clean $(EXE) run

$(EXE):
	$(CC) $(CFLAGS) $@.cpp -o $@.o
	$(CC) $@.o $(LFLAGS) -o $@

clean:
	rm -rf *.o $(EXE) *~

#clean:
#	rm -rf *.o $(EXE) JupiterSpice *~

run:
	./$(EXE)

plot:
	gnuplot script.gpl


