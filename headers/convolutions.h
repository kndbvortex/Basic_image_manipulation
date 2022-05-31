#ifndef CONVOLUTIONS_H_INCLUDED
#define CONVOLUTIONS_H_INCLUDED

/*  à définir */
void filtre_moyenneur(int **matrix_image, int row, int col, int rayon);
void filtre_gaussien(int **matrix_image, int row, int col, int **filtre, int row_filtre, int col_filtre);
void filtre_median(int **matrix_image, int row, int col, int row_filtre, int col_filtre);

#endif // CONVOLUTIONS_H