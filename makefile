default: serial_sim

main.o: src/main.c
	gcc -Wall -std=c99 -Iinc -c src/main.c

serial_sim.o: src/serial_sim.c
	gcc -Wall -std=c99 -Iinc -c src/serial_sim.c

fancy_print.o: src/fancy_print.c
	gcc -Wall -std=c99 -Iinc -c src/fancy_print.c

serial_sim: main.o serial_sim.o fancy_print.o
	gcc -Wall -std=c99 -Iinc -o serial_sim main.o serial_sim.o fancy_print.o

clean:
	rm main.o serial_sim.o fancy_print.o

cleanall: clean
	rm serial_sim
