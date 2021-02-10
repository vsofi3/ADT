CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs
PROGRAMS=reverse alreverse

all: $(PROGRAMS)

reverse: reverse.o stringlist.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

alreverse: alreverse.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

stringlist.o: stringlist.c stringlist.h
reverse.o: reverse.c stringlist.h

alreverse.o: alreverse.c 

clean:
	rm -f *.o $(PROGRAMS)
