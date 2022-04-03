#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

void hist(int ** matrix_image, int rows, int columns, int* hist);
int min(int **matrix_image, int rows, int columns);
int max(int **matrix_image, int rows, int columns);

// Opérations sur le contraste
int **contrast_linear_T(int **matrix_image, int rows, int columns);

#endif // OPERATIONS_H