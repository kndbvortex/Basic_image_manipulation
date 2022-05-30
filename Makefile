all:
	gcc -Wall main.c operations.c convolutions.c utils.c -I headers/ -lm -o main