IDIR =../include
CC=gcc
CFLAGS=-g -Wall -I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm


_DEPS = UncorrelatedClassifier.h FileInput.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = program1.o program2.o program3.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -$(OBJ) main