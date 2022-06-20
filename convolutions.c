#include <stdlib.h>
#include <stdio.h>
#include "headers/convolutions.h"
#include "headers/utils.h"


// Convolution
int **convolution(int **matrix_image, int row, int col, float **filtre, int row_filtre, int col_filtre)
{
    if (row_filtre % 2 == 0 || col_filtre % 2 == 0 || row_filtre != col_filtre)
    {
        printf("Opération non implémentée pour les filtres de taille Pair");
        exit(EXIT_FAILURE);
    }
    float conv_value = 0;
    int **result = allocateMatrix(row, col);
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            result[i][j] = 0;
    int rayon_row = (row_filtre - 1) / 2, rayon_col = (col_filtre - 1) / 2;

    float s = sumFloatMatrix(filtre, row_filtre, col_filtre);
    if (s != 0)
    {
        for (int i = 0; i < row_filtre; i++)
            for (int j = 0; j < col_filtre; j++)
                filtre[i][j] /= s;
    }

    for (int i = rayon_row; i < row - rayon_row; i++)
    {
        for (int j = rayon_col; j <= col - rayon_col; j++)
        {
            conv_value = 0.0;
            for (int k = -1 * rayon_row; k <= rayon_row; k++)
            {
                for (int l = -1 * rayon_col; l <= rayon_col; l++)
                {
                    conv_value += filtre[rayon_row + k][rayon_col + l] * matrix_image[i + k][j + l];
                }
            }
            if (conv_value < 0)
                conv_value *= -1;
            if (conv_value > 255)
                conv_value = 255;

            result[i][j] = conv_value;
        }
    }
    finTache("Convolution");
    return result;
}

void filtre_moyenneur(int **matrix_image, int row, int col, int rayon)
{

    int cote = 2 * rayon + 1;
    float **filtre = allocateFloatMatrix(cote, cote);
    for (int i = 0; i < cote; i++)
    {
        for (int j = 0; j < cote; j++)
        {
            filtre[i][j] = 1 / (float)(cote * cote);
        }
    }
    printf("Coté %d\n", cote);
    printFloatMatrix(filtre, cote, cote);
    int **result = convolution(matrix_image, row, col, filtre, cote, cote);
    finTache("Filtre moyenneur");
    writeImage("images/output/filtreMoyenneur.pgm", result, row, col);
}

int sumMatrix(int **matrix_image, int row, int col)
{
    int sum = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sum += matrix_image[i][j];
        }
    }
    return sum;
}
float sumFloatMatrix(float **filtre, int row, int col)
{
    float sum = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sum += filtre[i][j];
        }
    }
    return sum;
}

int is_gaussian(float **filter, int row, int col, int i, int j)
{
    if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
    {
        return 0;
    }

    int rayon = (row - 1) / 2;
    float val = filter[i][j];

    if (i == rayon && j == rayon)
    {
        for (int k = -1; k <= 1; k++)
        {
            for (int l = -1; l <= 1; l++)
            {
                if (filter[i + k][j + l] > val)
                    return 1;
            }
        }
        return 0;
    }
    else if (i < rayon)
    {
        if (j != rayon)
        {
            if (j > rayon)
            {
                if (filter[i - 1][j] > val || filter[i][j + 1] > val || filter[i - 1][j + 1] > val)
                    return 1;
            }
            else
            {
                if (filter[i - 1][j] > val || filter[i - 1][j - 1] > val || filter[i - 1][j + 1] > val)
                    return 1;
            }
            return 0;
        }
        else
        {
            if (filter[i - 1][j - 1] > val || filter[i - 1][j] > val || filter[i - 1][j + 1] > val)
                return 1;
            return 0;
        }
    }

    else if (i == rayon)
    {
        if (j < rayon)
        {
            if (filter[i - 1][j - 1] > val || filter[i][j - 1] > val || filter[i + 1][j - 1] > val)
                return 1;
        }
        else
        {
            if (filter[i - 1][j + 1] > val || filter[i][j + 1] > val || filter[i + 1][j + 1] > val)
                return 1;
        }
        return 0;
    }

    else if (i > rayon)
    {
        if (j == rayon)
        {
            if (filter[i + 1][j] > val || filter[i + 1][j - 1] > val || filter[i + 1][j + 1] > val)
                return 1;
        }
        else if (j < rayon)
        {
            if (filter[i + 1][j] > val || filter[i + 1][j - 1] > val || filter[i][j - 1] > val)
            {
                return 1;
            }
        }
        else
        {
            if (filter[i + 1][j] > val || filter[i + 1][j + 1] > val || filter[i][j + 1] > val)
            {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

void filtre_gaussien(int **matrix_image, int row, int col, int **filtre, int row_filtre, int col_filtre)
{
    if (row_filtre % 2 == 0 || col_filtre % 2 == 0 || row_filtre != col_filtre)
    {
        printf("Opération non implémentée pour les filtres de taille Pair");
        exit(EXIT_FAILURE);
    }
    float **gauss = allocateFloatMatrix(row_filtre, col_filtre);
    int s = sumMatrix(filtre, row_filtre, col_filtre);
    for (int i = 0; i < row_filtre; i++)
    {
        for (int j = 0; j < col_filtre; j++)
            gauss[i][j] = (float)filtre[i][j] / s;
    }

    for (int i = 0; i < row_filtre; i++)
    {
        for (int j = 0; j < col_filtre; j++)
        {
            if ((is_gaussian(gauss, row_filtre, col_filtre, i, j)) != 0)
            {
                printf("Entrez une Gaussienne valide à l'indexe (%d, %d)!!\n", i, j);
                printFloatMatrix(gauss, row_filtre, col_filtre);
                exit(EXIT_FAILURE);
            }
        }
    }
    printf("Filtre Gaussien valide\n");
    int **result = convolution(matrix_image, row, col, gauss, row_filtre, col_filtre);
    finTache("Filtre Gaussien");
    writeImage("images/output/filtreGaussien.pgm", result, row, col);
    free(result);
}

void filtre_median(int **matrix_image, int row, int col, int row_filtre, int col_filtre)
{
    if (row_filtre % 2 == 0 || col_filtre % 2 == 0 || row_filtre != col_filtre)
    {
        printf("Opération non implémentée pour les filtres de taille Pair");
        exit(EXIT_FAILURE);
    }
    int *array = allocateVector(row_filtre * col_filtre);
    int **result = allocateMatrix(row, col);
    int rayon_row = (row_filtre - 1) / 2, rayon_col = (col_filtre - 1) / 2;
    int indice = 0, tmp = 0;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            result[i][j] = 0;

    for (int i = rayon_row; i < row - rayon_row; i++)
    {
        for (int j = rayon_col; j <= col - rayon_col; j++)
        {
            for (int k = -1 * rayon_row; k <= rayon_row; k++)
            {
                for (int l = -1 * rayon_col; l <= rayon_col; l++)
                {
                    array[indice] = matrix_image[i + k][j + l];
                    for (int s = indice; s > 0; s--)
                    {
                        if (array[s - 1] > array[s])
                        {
                            tmp = array[s - 1];
                            array[s - 1] = array[s];
                            array[s] = tmp;
                        }

                        else
                            break;
                    }
                    indice++;
                }
            }
            result[i][j] = array[(row_filtre * col_filtre - 1) / 2];
            indice = 0;
        }
    }
    finTache("Filtre Médian");
    writeImage("images/output/filtreMedian.pgm", result, row, col);
}

void contour_sobel(int **matrix, int row, int col, int seuil)
{
    int col_f = 0, row_f = 0;
    float **s_x = readFloatFilter("filtres/sobel_x.txt", &row_f, &col_f);
    float **s_y = readFloatFilter("filtres/sobel_y.txt", &row_f, &col_f);
    int **Gx = convolution(matrix, row, col, s_x, row_f, col_f);
    int **Gy = convolution(matrix, row, col, s_y, row_f, col_f);
    int **sobel = allocateMatrix(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            sobel[i][j] = Gx[i][j] + Gy[i][j];
            if (sobel[i][j] > 255)
            {
                sobel[i][j] = 255;
            }
            if(seuil != -1){
                if(sobel[i][j] >= seuil)
                    sobel[i][j] = 255;
                else
                    sobel[i][j] = 0;
            }
        }
    }
    writeImage("images/output/sobel.pgm", sobel, row, col);
    free(sobel);
    free(Gx);
    free(Gy);
}
void contour_prewitt(int **matrix, int row, int col, int seuil){
    int col_f = 0, row_f = 0;
    float **p_x = readFloatFilter("filtres/prewitt_x.txt", &row_f, &col_f);
    float **p_y = readFloatFilter("filtres/prewitt_y.txt", &row_f, &col_f);
    int **Gx = convolution(matrix, row, col, p_x, row_f, col_f);
    int **Gy = convolution(matrix, row, col, p_y, row_f, col_f);
    int **prewitt = allocateMatrix(row, col);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            prewitt[i][j] = Gx[i][j] + Gy[i][j];
            if (prewitt[i][j] > 255)
            {
                prewitt[i][j] = 255;
            }
            if (seuil != -1)
            {
                if (prewitt[i][j] >= seuil)
                    prewitt[i][j] = 255;
                else
                    prewitt[i][j] = 0;
            }
        }
    }
    writeImage("images/output/prewitt.pgm", prewitt, row, col);
    free(prewitt);
    free(Gx);
    free(Gy);
}
void contour_laplacien(int **matrix, int row, int col, int seuil){
    int col_f = 0, row_f = 0;
    float **H = readFloatFilter("filtres/laplacien.txt", &row_f, &col_f);
    int **laplacien = convolution(matrix, row, col, H, row_f, col_f);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (seuil != -1)
            {
                if (laplacien[i][j] >= seuil)
                    laplacien[i][j] = 255;
                else
                    laplacien[i][j] = 0;
            }
        }
    }
    writeImage("images/output/laplacien.pgm", laplacien, row, col);
    free(laplacien);
    free(H);
}