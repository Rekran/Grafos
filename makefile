CC = g++

all:
	$(CC) main.cpp grafo.cpp -g3 -o main

clean:
	rm main