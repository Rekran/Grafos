CC = g++

all:
	$(CC) main.cpp grafo.cpp -o main

clean:
	rm main