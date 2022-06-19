#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "headers/operations.h"
#include "headers/utils.h"
#include "headers/convolutions.h"
#include "headers/fourier.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        int rows = 0, columns = 0;
        if (strcmp(argv[1], "hist") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int *histogram = hist(matrix_image, rows, columns);
            int m = 0;
            for(int i=0; i<256; i++){
                if(histogram[i] > m)
                    m=histogram[i];
            }
            writeHistogram(histogram, m);
            free(matrix_image);
            free(histogram);
        }
        else if (strcmp(argv[1], "luminance") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            printf("La luminance de l'image est %f\n", luminance(matrix_image, rows, columns));
            free(matrix_image);
        }
        else if (strcmp(argv[1], "transLineaire") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            free(contrast_linear_T(matrix_image, rows, columns));
            free(matrix_image);
        }
        else if (strcmp(argv[1], "transAvecSat") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            free(contrast_linear_avec_saturation(matrix_image, rows, columns, atoi(argv[3]), atoi(argv[4])));
            free(matrix_image);
        }
        else if (strcmp(argv[1], "inverse") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            free(inverseImage(matrix_image, rows, columns));
            free(matrix_image);
        }
        else if (strcmp(argv[1], "egalisation") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            free(egalisationHistogram(matrix_image, rows, columns));
            free(matrix_image);
        }
        else if (strcmp(argv[1], "ou") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int row = 0, col = 0;
            int **bin_image = readImage(argv[3], &row, &col);
            free(OULogique(matrix_image, rows, columns, bin_image, row, col));
            free(matrix_image);
            free(bin_image);
        }
        else if (strcmp(argv[1], "et") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int row = 0, col = 0;
            int **bin_image = readImage(argv[3], &row, &col);
            free(ETLogique(matrix_image, rows, columns, bin_image, row, col));
            free(matrix_image);
            free(bin_image);
        }
        else if (strcmp(argv[1], "xor") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int row = 0, col = 0;
            int **bin_image = readImage(argv[3], &row, &col);
            free(XORLogique(matrix_image, rows, columns, bin_image, row, col));
            free(matrix_image);
            free(bin_image);
        }
        else if (strcmp(argv[1], "addition") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int row = 0, col = 0;
            int **bin_image = readImage(argv[3], &row, &col);
            free(addition(matrix_image, rows, columns, bin_image, row, col));
            free(matrix_image);
            free(bin_image);
        }
        else if (strcmp(argv[1], "soustraction") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int row = 0, col = 0;
            int **bin_image = readImage(argv[3], &row, &col);
            free(soustraction(matrix_image, rows, columns, bin_image, row, col));
            free(matrix_image);
            free(bin_image);
        }
        else if (strcmp(argv[1], "multiplication") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            free(multiplication(matrix_image, rows, columns, atof(argv[3])));
            free(matrix_image);
        }
        else if (strcmp(argv[1], "interploationSimple") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            interpolationSimple(matrix_image, rows, columns, atof(argv[3]) * rows, atof(argv[3]) * columns);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "interpolationBilineaire") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            interpolationBilineaire(matrix_image, rows, columns, atof(argv[3]) * rows, atof(argv[3]) * columns);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "interpolationBicubique") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            interpolationBicubique(matrix_image, rows, columns, atof(argv[3]) * rows, atof(argv[3]) * columns);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "rotation") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            rotation(matrix_image, rows, columns, atof(argv[3]));
            free(matrix_image);
        }
        else if (strcmp(argv[1], "convolution") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int row_f = 0, col_f;
            float **filtre_convo = readFloatFilter("filtres/convo.txt", &row_f, &col_f);
            int **img_conv = convolution(matrix_image, rows, columns, filtre_convo, row_f, col_f);
            writeImage("images/output/convolution.pgm", img_conv, rows, columns);
            free(filtre_convo);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "filtreMoyenneur") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            filtre_moyenneur(matrix_image, rows, columns, atoi(argv[3]));
            free(matrix_image);
        }
        else if (strcmp(argv[1], "filtreGaussien") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int row_filter = 0, col_filter = 0;
            int **gauss = readFilter("filtres/gauss.txt", &row_filter, &col_filter);
            filtre_gaussien(matrix_image, rows, columns, gauss, row_filter, col_filter);
            free(matrix_image);
            free(gauss);
        }
        else if (strcmp(argv[1], "filtreMedian") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            filtre_median(matrix_image, rows, columns, atoi(argv[3]), atoi(argv[3]));
            free(matrix_image);
        }
    }
    //int rows = 0, columns = 0, row2 = 0, col2 = 0, row3 = 0, col3 = 0;
    // int **matrix_image = readImage("images/input/tour.pgm", &rows, &columns);
    // int **bin_image = readImage("images/input/imagebin.pgm", &rows, &columns);
    // int **bin_image2 = readImage("images/input/imagebin2.pgm", &row2, &col2);
    // int **matrix_image = readImage("images/input/fillet.pgm", &rows, &columns);
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
    // hist(matrix_image, rows, columns);
    // filtre_moyenneur(matrix_image, rows, columns, 2);
    // int row_filter = 0, col_filter = 0;
    // int **gauss = readFilter("filtres/gauss.txt", &row_filter, &col_filter);
    // // printMatrix(gauss, row_filter, col_filter);
    // filtre_gaussien(matrix_image, rows, columns, gauss, row_filter, col_filter);
    // filtre_median(matrix_image, rows, columns, 3, 3);
    // transformer_fourier(matrix_image, rows, columns);
    return 0;
}