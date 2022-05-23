#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#define IMAGE_INPUT_FOLDER "images/input/"
#define IMAGE_OUTPUT_FOLDER "images/output/"

void printArray(int *array, int lenght);
void printMatrix(int **matrix, int rows, int columns);

int **allocateMatrix(int rows, int columns);

int **readImage(char filename[], int *rows, int *columns);
void writeImage(char filename[], int **matrix_image, int rows, int columns);

#endif 