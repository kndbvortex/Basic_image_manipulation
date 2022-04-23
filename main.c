#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "headers/operations.h"
#include "headers/utils.h"

int main(int argc, char *argv[])
{
    int *hist_value;
    if (argc > 1)
    {
        for (int j = 1; j < argc; j++)
            printf("%s ......\n", argv[j]);
    }
    else
    {
        printf("%d....", argc);
    }
    int rows = 0, columns = 0;
    int **matrix_image = readImage("images/usine.pgm", &rows, &columns);
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
    int seuils[] = {10, 100}, cord_ord[] = {256 / 8, 7 * 256 / 8};
    double coef_dir[] = {0.1, 0.86};
    transformation_lineaire_par_morceau(matrix_image, rows, columns, coef_dir, cord_ord, seuils, 2);

    return 0;
}