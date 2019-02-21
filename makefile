CC=gcc
SRCDIR=src
INCDIR=inc
OBJDIR=obj
CVER=c99
CFLAGS=-Wall -std=$(CVER) -I$(INCDIR)

default: serial_sim

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

serial_sim.o: src/serial_sim.c
	$(CC) $(CFLAGS) -c src/serial_sim.c

fancy_print.o: src/fancy_print.c
	$(CC) $(CFLAGS) -c src/fancy_print.c

serial_sim: main.o serial_sim.o fancy_print.o
	$(CC) $(CFLAGS) -o serial_sim main.o serial_sim.o fancy_print.o

clean:
	rm main.o serial_sim.o fancy_print.o

cleanall: clean
	rm serial_sim
