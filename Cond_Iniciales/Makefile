CC = g++
CFLAGS_OPT=-O4 -Wall
SPICEPATH=../UTILPROG/cspice
CPPFLAGS=$(CFLAGS_OPT) -I. -I$(SPICEPATH)/include
CSPICE_LIBDIR=$(SPICEPATH)/lib64
PROGS=Cond_Ini.out Earth.out

CSPICE_LIBS=$(CSPICE_LIBDIR)/cspice.a $(CSPICE_LIBDIR)/csupport.a
LFLAGS=-lm $(CSPICE_LIBS)


# EXE = Cond_Ini
# EXE= JupiterSpice

# show:
# 	@echo "Compiling"

all:$(PROGS)
	@echo "COMPILING...." $^


%.out:%.o
	${CC} $< ${LFLAGS} -o $@
	cp -rf $@ $(@:.out=)

# $(EXE):
# 	$(CC) $(CFLAGS) $@.cpp -o $@.o
# 	$(CC) $@.o $(LFLAGS) -o $@

clean:
	rm -rf *.o $(PROGS) $(PROGS:.out=) *~ 
	rm -rf *.dat *.pos *.state *.txt

# cleanbc:
# 	rm -rf *.o *~ *.pos JupiterPos.dat

# run:
# 	./$(EXE)

plot:
	gnuplot script.gpl


