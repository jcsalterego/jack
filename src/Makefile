
CC=gcc
CPPFLAGS=-Wall -O3 -pg -g -I.
CPPFLAGS_EXTRA=\
	$(CPPFLAGS) \
	-Waggregate-return \
	-Wcast-align \
	-Wcast-qual \
	-Wconversion \
	-Wextra \
	-Wfloat-equal \
	-Wno-unused-parameter \
	-Wpointer-arith \
	-Wshadow \
	-Wstrict-overflow=5 \
	-Wstrict-prototypes \
	-Wswitch-default \
	-Wswitch-enum \
	-Wundef \
	-Wwrite-strings

LDFLAGS=

all: jack
EXES=jack

jack: jack.o globals.h options.o
	$(CC) $(LDFLAGS) $(CPPFLAGS_EXTRA) $+ -o jack
%.o: %.c
	$(CC) -c $(CPPFLAGS_EXTRA) $+ -o $@
clean:
	rm -rf $(EXES) *~ \#*\# *.o gmon.out *.dSYM/
