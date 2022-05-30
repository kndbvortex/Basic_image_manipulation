#include <stdlib.h>
#include <stdio.h>
#include "headers/convolutions.h"
#include "headers/utils.h"

// Rotation du filtre
void rotation_filtre(float **filtre, int row, int col)
{
    float tmp = 0.0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            tmp = filtre[i][j];
            filtre[i][j] = filtre[row - 1 - i][col - 1 - j];
            filtre[row - 1 - i][col - 1 - j] = tmp;
        }
    }
}

// Convolution
int **convolution(int **matrix_image, int row, int col, float **filtre, int row_filtre, int col_filtre)
{
    if (row_filtre % 2 == 0 || col_filtre % 2 == 0 || row_filtre != col_filtre)
    {
        printf("Opération non implémentée pour les filtres de taille Pair");
        exit(EXIT_FAILURE);
    }
    float conv_value = 0;
    rotation_filtre(filtre, row_filtre, col_filtre);
    int **result = allocateMatrix(row, col);
    int rayon_row = (row_filtre - 1) / 2, rayon_col = (col_filtre - 1) / 2;

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
            result[i][j] = conv_value;
        }
    }
    finTache("Convolution");
    writeImage("images/output/convolution.pgm", result, row, col);
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

    int rayon = (row + 1) / 2;
    float val = filter[i][j];

    if (i == rayon -1 && j == rayon-1)
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
        int indice_decal = 0;
        if (j != rayon)
        {
            if (j > rayon)
                indice_decal = 1;
            else
                indice_decal = -1;
            if (filter[i + indice_decal][j] > val || filter[i + indice_decal][j + indice_decal] > val || filter[i][j + indice_decal] > val)
                return 1;
            return 0;
        }
        else
        {
            int indice = 0;
            if(j == rayon){
                if (filter[i - 1][j - 1] > val || filter[i-1][j] > val || filter[i - 1][j + 1] > val)
                    return 1;
                return 0;
            }

            if (filter[i - 1][j - 1] > val || filter[i][j - 1] > val || filter[i + 1][j - 1] > val)
                return 1;
            return 0;
        }
    }
    else{
        int indice_decal = 0;
        if (i != rayon - 1)
        {
            if (j < rayon)
                indice_decal = -1;
            else
                indice_decal = 1;
            
            if (filter[i][j+indice_decal] > val || filter[i+1][j] > val || filter[i+indice_decal][j + indice_decal] > val){
                return 1;
            }
                
            return 0;
        }
        else
        {
            if (filter[i + 1][j + 1] > val || filter[i][j + 1] > val || filter[i - 1][j + 1] > val)
                return 1;
            return 0;
        }
    }    
}


void filtre_gaussien(int **matrix_image, int row, int col, int** filtre, int row_filtre, int col_filtre)
{
    if (row_filtre % 2 == 0 || col_filtre % 2 == 0 || row_filtre != col_filtre)
    {
        printf("Opération non implémentée pour les filtres de taille Pair");
        exit(EXIT_FAILURE);
    }
    float **gauss = allocateFloatMatrix(row_filtre, col_filtre);
    int s = sumMatrix(filtre, row_filtre, col_filtre);
    for (int i = 0; i < row_filtre; i++){
        for (int j = 0; j < col_filtre; j++)
            gauss[i][j] = (float)filtre[i][j] / s;
    }

    for(int i=0; i<row_filtre; i++){
        for(int j=0; j<col_filtre; j++){
            if((is_gaussian(gauss, row_filtre, col_filtre, i, j)) != 0){
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