# Build the CUDD tutorials against an installed CUDD.
#
# CUDD must already be built and installed (see tutorials/README.md).
# CUDD defaults to /usr/local, the configure script's default prefix.

CUDD ?= /usr/local

CC      = gcc
CFLAGS  = -Wall -Wextra -g -O2 -I$(CUDD)/include
LDFLAGS = -L$(CUDD)/lib
LDLIBS  = -lcudd -lm

PROGRAMS = tutorial1 tutorial2

.PHONY: all run clean

all: $(PROGRAMS)

tutorial1: tutorial1.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

tutorial2: tutorial2.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

# Run both tutorials. Each writes its own .dot file into bdd/.
run: $(PROGRAMS)
	./tutorial1
	./tutorial2

clean:
	rm -f $(PROGRAMS)
	rm -rf bdd
