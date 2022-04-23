all:
	gcc -Wall main.c operations.c utils.c -I headers/ -lm -o main