CPP=g++
CFLAGS_OPT=-O4
SPICEPATH=cspice
CPPFLAGS=$(CFLAGS_OPT) -I. -I$(SPICEPATH)/include
CSPICE_LIBDIR=$(SPICEPATH)/lib64
UTILPROGS=xyz2aei.out aei2xyz.out GetState.out

CSPICE_LIBS=$(CSPICE_LIBDIR)/cspice.a $(CSPICE_LIBDIR)/csupport.a
LFLAGS=-lm $(CSPICE_LIBS)

all:$(UTILPROGS)
	@echo "\nCOMPILING...." $^

install:
	cp -rf $(UTILPROGS:.out=) ../BIN

%.out:%.o
	@echo "\nCompiling..." $@
	${CPP} $< ${LFLAGS} -o $@
	cp -rf $@ $(@:.out=)

clean:
	@echo "Cleaning..."
	rm -rf *.out *~
	rm -rf $(UTILPROGS:.out=)
	cd ../BIN;rm -rf $(UTILPROGS:.out=)