CC=g++
CFLAGS_OPT=-O4
CPPFLAGS=$(CFLAGS_OPT) -I.
PROGRAMS=CaptureT.out OE_END_SUN.out OE_Final_Jupiter.out OrbElm_Jup2Sun.out
LFLAGS=-lm

all:$(PROGRAMS)
	@echo "\nCOMPILING PROGRAMS..." $^

%.out:%.o
	@echo "\nCreating file " $@
	${CC} $< ${LFLAGS} -o $@
	#cp -rf $@ $(@:.out=)

clean:
	@echo "Cleaning files in folder Analysis ....."
	rm -rf *.out
	rm -rf $(PROGRAMS:.out=)