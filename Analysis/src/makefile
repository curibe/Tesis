CC=g++

FLAGSCPP= -Wall -I.
CFLAGS=-c -O4 $(FLAGSCPP)
LFLAGS=-lm

PROGRAMS=CaptureT.out OE_END_SUN.out OE_Final_Jupiter.out OrbElm_Jup2Sun.out EQCoord.out

all:$(PROGRAMS)


%.out:%.o
	${CC} $< ${LFLAGS} -o $@
	#cp -rf $@ $(@:.out=)

%.o:%.cpp
	@echo "\nCOMPILING FILE ..." $^
	$(CC) $< ${CFLAGS} -o $@


clean:
	@echo "Cleaning files in folder Analysis ....."
	rm -rf *.out
	rm -rf *.pyc *.txt *~
	rm -rf $(PROGRAMS:.out=)