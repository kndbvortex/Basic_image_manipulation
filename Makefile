all:
	gcc -Wall main.c operations.c convolutions.c utils.c fourier.c -I headers/ -lm -o main

conv: conv.c
	gcc -Wall conv.c utils.c -I headers/ -o conv 