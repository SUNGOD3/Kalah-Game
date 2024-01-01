all: main

main: main.o
	gcc -o main main.o game.o
	
main.o: main.c
	gcc -c main.c

.PHONY: clean

clean:
	rm main main.o