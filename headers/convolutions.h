#ifndef CONVOLUTIONS_H_INCLUDED
#define CONVOLUTIONS_H_INCLUDED

/*  à définir */

int sumMatrix(int **matrix_image, int row, int col);
float sumFloatMatrix(float **filtre, int row, int col);
int **convolution(int **matrix_image, int row, int col, float **filtre, int row_filtre, int col_filtre);
int **filtre_moyenneur(int **matrix_image, int row, int col, int rayon);
void filtre_gaussien(int **matrix_image, int row, int col, int **filtre, int row_filtre, int col_filtre);
void filtre_median(int **matrix_image, int row, int col, int row_filtre, int col_filtre);
int **contour_robert(int **matrix, int row, int col, int seuil);
int **contour_sobel(int **matrix, int row, int col, int seuil);
void contour_prewitt(int **matrix, int row, int col, int seuil);
void contour_laplacien(int **matrix, int row, int col, int seuil);

void transformee_hough(int **matrix, int row, int col, int seuil, int seuil_vote);

#endif // CONVOLUTIONS_H