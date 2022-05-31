#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "headers/operations.h"
#include "headers/utils.h"
#include "headers/convolutions.h"

int main(int argc, char *argv[])
{
    // int *hist_value;
    if (argc > 1)
    {
        for (int j = 1; j < argc; j++)
            printf("%s ......\n", argv[j]);
    }
    else
    {
        printf("%d....\n", argc);
    }
    int rows = 0, columns = 0, row2 = 0, col2 = 0, row3 = 0, col3 = 0;
    // int **matrix_image = readImage("images/input/tour.pgm", &rows, &columns);
    // int **bin_image = readImage("images/input/imagebin.pgm", &rows, &columns);
    // int **bin_image2 = readImage("images/input/imagebin2.pgm", &row2, &col2);
    int **matrix_image = readImage("images/input/filtreMedian.pgm", &rows, &columns);
    // int **matrix_image2 = readImage("images/input/arithmetique2.pgm", &row2, &col2);
    // int **matrix_image3 = readImage("images/input/terre.pgm", &row3, &col3);
    // hist_value = hist(matrix_image, rows, columns);
    // printArray(hist_value, 255);
    // printf("min: %d, max: %d", min(matrix_image, rows, columns), max(matrix_image, rows, columns));
    // int **contrast = contrast_linear_T(matrix_image, rows, columns);
    // int **contrast_saturation = contrast_linear_avec_saturation(matrix_image, rows, columns, 100, 200);
    // int **inverse_of_image = inverseImage(matrix_image, rows, columns);
    // writeImage("images/testcontrast.pgm", inverse_of_image, rows, columns);
    // int **hist_egalise = egalisationHistogram(matrix_image, rows, columns);
    // writeImage("images/egalise.pgm", hist_egalise, rows, columns);
    // transformation_par_log(matrix_image, rows, columns);
    // int seuils[] = {10, 100}, cord_ord[] = {256 / 8, 7 * 256 / 8};
    // double coef_dir[] = {0.1, 0.86};
    // transformation_lineaire_par_morceau(matrix_image, rows, columns, coef_dir, cord_ord, seuils, 2);

    // ETLogique(matrix_image, rows, columns, bin_image, row2, col2);
    //  XORLogique(bin_image, rows, columns, bin_image2, row2, col2);
    //  addition(matrix_image, rows, columns, matrix_image2, row2, col2);
    //  soustraction(matrix_image2, row2, col2, matrix_image, rows, columns);
    //  int ** im1 = multiplication(matrix_image, rows, columns, 0.5);
    //  int **im2 = multiplication(matrix_image2, rows, columns, 0.5);
    //  addition(im1, rows, columns, im2, row2, col2);
    // interpolationSimple(matrix_image, rows, columns, 2*rows, 2*columns);
    // interpolationBilineaire(matrix_image, rows, columns, 2*rows, 2*columns);
    // interpolationBicubique(matrix_image, rows, columns, 2 * rows, 2 * columns);
    // rotation(matrix_image, rows, columns, 190);
    filtre_moyenneur(matrix_image, rows, columns, 2);
    // int row_filter = 0, col_filter = 0;
    // int** gauss = readFilter("filtres/gauss.txt", &row_filter, &col_filter);
    // printMatrix(gauss, row_filter, col_filter);
    // filtre_gaussien(matrix_image, rows, columns, gauss, row_filter, col_filter);
    filtre_median(matrix_image, rows, columns, 3, 3);
    return 0;
}