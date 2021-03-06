#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// éléments de base
int *hist(int **matrix_image, int rows, int columns, int start_x, int start_y);
double *hist_normalise(int **matrix_image, int rows, int columns);
int min(int **matrix_image, int rows, int columns);
int max(int **matrix_image, int rows, int columns);
double luminance(int **matrix_image, int rows, int columns);

// Binariser une image
int seuil_otsu(int **matrix_image, int rows, int columns, int start_x, int start_y);
int **seuillage(int **matrix_image, int rows, int columns, int seuil);
int **seuillage_adaptatif(int **matrix_image, int row, int col, int nbre_region_x, int nbre_region_y, char type[]);
int **k_means(int **matrix, int row, int col, int k);
int **division_fusion(int **matrix, int row, int col, int critere);

int **rogner(int **matrix_image, int rows, int columns, int new_row, int new_columns);

// Opérations sur le contraste
int **contrast_linear_T(int **matrix_image, int rows, int columns);
int **contrast_linear_avec_saturation(int **matrix_image, int rows, int columns, int smin, int smax);
int **transformation_lineaire_par_morceau(int **matrix_image, int rows, int columns, double coef_dir[], int cord_ord[], int seuils[], int n);

// à definir
int **contrast_non_linear();

// Inversion de l'image
int **inverseImage(int **matrix_image, int rows, int columns);

// Égalisation d'histogramme
int **egalisationHistogram(int **matrix_image, int rows, int columns);

// Opérations logiques
int **OULogique(int **matrix_image, int row1, int col1, int **bin_matrix, int row2, int col2);
int **ETLogique(int **matrix_image, int row1, int col1, int **bin_matrix, int row2, int col2);
int **XORLogique(int **bin_image, int row1, int col1, int **bin_image2, int row2, int col2);

// Opérations arithmétiques
int **addition(int **matrix_image, int row1, int col1, int **matrix_image2, int row2, int col2);
int **soustraction(int **matrix_image, int row1, int col1, int **matrix_image2, int row2, int col2);
int **multiplication(int **matrix_image, int row1, int col1, float ratio);

// Opération d'interpolation
void interpolationSimple(int **matrix_image, int row, int col, int new_row, int new_col);
int** interpolationBilineaire(int **matrix_image, int row, int col, int new_row, int new_col);
void interpolationBicubique(int **matrix_image, int row, int col, int new_row, int new_col);

// à terminer
void rotation(int **matrix_image, int row, int col, float angle);

#endif // OPERATIONS_H