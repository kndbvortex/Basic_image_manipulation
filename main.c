#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "headers/operations.h"
#include "headers/utils.h"
#include "headers/convolutions.h"
#include "headers/fourier.h"

struct pixel_index
{
    int niveau_gris;
    int nbre;
};
typedef struct pixel_index pixel_index;

int cmpfunc(const pixel_index *a, const pixel_index *b)
{
    return (a->nbre - b->nbre);
}
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        int rows = 0, columns = 0;
        if (strcmp(argv[1], "histogramme") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int *histogram = hist(matrix_image, rows, columns, 0, 0);
            int m = 0;
            for (int i = 0; i < 256; i++)
            {
                if (histogram[i] > m)
                    m = histogram[i];
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
            int *histo = hist(matrix_image, rows, columns, 0, 0);
            int m = 0;
            for (int i = 0; i < 256; i++)
            {
                if (histo[i] > m)
                    m = histo[i];
            }
            writeHistogram(histo, m);
            int **egal_matrix = egalisationHistogram(matrix_image, rows, columns);
            histo = hist(egal_matrix, rows, columns, 0, 0);
            m = 0;
            for (int i = 0; i < 256; i++)
            {
                if (histo[i] > m)
                    m = histo[i];
            }
            writeHistogram(histo, m);
            free(histo);
            free(egal_matrix);
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
        else if (strcmp(argv[1], "addMultiplication") == 0)
        {
            int col, row;
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int **matrix_image2 = readImage(argv[4], &row, &col);
            float c1 = atof(argv[3]), c2 = atof(argv[5]);
            int **m = multiplication(matrix_image, rows, columns, c1);
            int **n = multiplication(matrix_image2, row, col, c2);
            free(addition(m, rows, columns, n, row, col));
            free(matrix_image);
            free(matrix_image2);
        }

        else if (strcmp(argv[1], "sousMultiplication") == 0)
        {
            int col, row;
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int **matrix_image2 = readImage(argv[4], &row, &col);
            float c1 = atof(argv[3]), c2 = atof(argv[5]);
            int **m = multiplication(matrix_image, rows, columns, c1);
            int **n = multiplication(matrix_image2, row, col, c2);
            free(soustraction(m, rows, columns, n, row, col));
            free(matrix_image);
            free(matrix_image2);
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
        else if (strcmp(argv[1], "contourPrewit") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int seuil = -1;
            if (argc >= 4)
                seuil = atoi(argv[3]);
            contour_prewitt(matrix_image, rows, columns, seuil);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "contourSobel") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int seuil = -1;
            if (argc >= 4)
                seuil = atoi(argv[3]);
            contour_sobel(matrix_image, rows, columns, seuil);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "contourLaplace") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int seuil = -1;
            if (argc >= 4)
                seuil = atoi(argv[3]);
            contour_laplacien(matrix_image, rows, columns, seuil);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "hough") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int seuil = -1, seuil_h = -1;
            if (argc >= 4)
                seuil = atoi(argv[3]);
            if (argc >= 5)
                seuil_h = atoi(argv[4]);
            transformee_hough(matrix_image, rows, columns, seuil, seuil_h);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "binarisation") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            int seuil = 0;
            if (argc == 4)
            {
                if (strcmp(argv[3], "moyenne") == 0)
                {
                    seuil = luminance(matrix_image, rows, columns);
                }
                else if (strcmp(argv[3], "mediane") == 0)
                {
                    int min_image = min(matrix_image, rows, columns);
                    int max_image = max(matrix_image, rows, columns);
                    int *h = hist(matrix_image, rows, columns, 0, 0);
                    pixel_index *tab = malloc((max_image - min_image + 1) * sizeof(pixel_index));
                    for (int i = min_image; i <= max_image; i++)
                    {
                        tab[i - min_image].nbre = h[i];
                        tab[i - min_image].niveau_gris = i;
                    }
                    free(h);
                    qsort(tab, max_image - min_image + 1, sizeof(int), cmpfunc);
                    seuil = tab[(max_image - min_image + 1) / 2].niveau_gris;
                    free(tab);
                }
                else if (strcmp(argv[3], "automatique") == 0)
                {
                    seuil = seuil_otsu(matrix_image, rows, columns, 0, 0);
                }
                
            }
            else if (argc == 5){
                seuil = atoi(argv[4]);
            }
            printf("Seuil = %d\n", seuil);
            writeImage("images/output/binarisation.pgm", seuillage(matrix_image, rows, columns, seuil), rows, columns);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "seuillageAdaptatif") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            seuillage_adaptatif(matrix_image, rows, columns, atoi(argv[3]), atoi(argv[4]), argv[5]);
            free(matrix_image);
        }
        else if (strcmp(argv[1], "k-means") == 0)
        {
            int **matrix_image = readImage(argv[2], &rows, &columns);
            k_means(matrix_image, rows, columns, atoi(argv[3]));
            free(matrix_image);
        }
    }
    
    // int rows = 0, columns = 0, row2 = 0, col2 = 0, row3 = 0, col3 = 0;
    // int **matrix_image = readImage("images/input/personne.pgm", &rows, &columns);
    // k_means(matrix_image, rows, columns, 4);
    // printf("%d\n", 207/52);
    // seuillage_adaptatif(matrix_image, rows, columns, 12, 20);
    // int **co = filtre_moyenneur(matrix_image, rows, columns, 3);
    // int **s = soustraction(matrix_image, rows, columns, co, rows, columns);
    // //writeImage("images/output/test.pgm", s, rows, columns);
    // s=egalisationHistogram(s, rows, columns);
    // s=inverseImage(s, rows, columns);

    // transformee_hough(matrix_image, rows, columns, -1, 120);
    // contour_prewitt(matrix_image, rows, columns, -1);
    // contour_laplacien(matrix_image, rows, columns, -1);

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