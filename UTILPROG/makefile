CC=g++

SPICEPATH=cspice
CSPICE_LIBDIR=$(SPICEPATH)/lib64
CSPICE_LIBS=$(CSPICE_LIBDIR)/cspice.a $(CSPICE_LIBDIR)/csupport.a
FLAGSCPP= -Wall -I. -I$(SPICEPATH)/include
CFLAGS=-c -O4 $(FLAGSCPP)
LFLAGS=-lm $(CSPICE_LIBS)

UTILPROGS=xyz2aei.out aei2xyz.out GetState.out



all:$(UTILPROGS)
	@echo "\nCOMPILING...." $^


install:
	cp -rf $(UTILPROGS) ../BIN



%.out:%.o
	@echo "\nCompiling..." $@
	$(CC) $< ${LFLAGS} -o $@
	#cp -rf $@ $(@:.out=)

%.o:%.cpp
	@echo "\nCreation file.o ..."
	$(CC) $< $(CFLAGS) -o $@



clean:
	@echo "Cleaning..."
	rm -rf *.out *~
	rm -rf $(UTILPROGS:.out=)
	cd ../BIN;rm -rf $(UTILPROGS:.out=) $(UTILPROGS)