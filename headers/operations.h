#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

int *hist(int **matrix_image, int rows, int columns);
double *hist_normalise(int **matrix_image, int rows, int columns);
int min(int **matrix_image, int rows, int columns);
int max(int **matrix_image, int rows, int columns);
double luminance(int **matrix_image, int rows, int columns);

// Binariser une image
int **seuillage(int **matrix_image, int rows, int columns, int seuil);

int **rogner(int **matrix_image, int rows, int columns, int new_row, int new_columns);

// Opérations sur le contraste
int **contrast_linear_T(int **matrix_image, int rows, int columns);
int **contrast_linear_avec_saturation(int **matrix_image, int rows, int columns, int smin, int smax);
int **transformation_lineaire_par_morceau(int **matrix_image, int rows, int columns, double coef_dir[], int cord_ord[], int seuils[], int n);

// à définir
int **transformation_par_log(int **matrix_image, int rows, int columns);

// à definir
int **contrast_non_linear();

// Inversion de l'image
int **inverseImage(int **matrix_image, int rows, int columns);

int **egalisationHistogram(int **matrix_image, int rows, int columns);

int **OULogique(int **matrix_image, int row1, int col1, int **bin_matrix, int row2, int col2);
int **ETLogique(int **matrix_image, int row1, int col1, int **bin_matrix, int row2, int col2);

#endif // OPERATIONS_H