default: test_vr_serial

main.o: src/main.c
	gcc -Wall -std=c99 -Iinc -c src/main.c

vr_serial.o: src/vr_serial.c
	gcc -Wall -std=c99 -Iinc -c src/vr_serial.c

fancy_print.o: src/fancy_print.c
	gcc -Wall -std=c99 -Iinc -c src/fancy_print.c

test_vr_serial: main.o vr_serial.o fancy_print.o
	gcc -Wall -std=c99 -Iinc -o test_vr_serial main.o vr_serial.o fancy_print.o

clean:
	rm main.o vr_serial.o fancy_print.o

cleanall: clean
	rm test_vr_serial
