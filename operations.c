#include "headers/operations.h"

void hist(int **matrix_image, int rows, int columns, int *hist)
{
    printf("%d\n", rows);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            hist[matrix_image[i][j] - 1]++;
        }
    }
}

int min(int **matrix_image, int rows, int columns){
    int val_min = 255;
    for(int i = 0; i<rows; i++){
        for(int j=0; j<columns; j++){
            if(val_min > matrix_image[i][j]){
                val_min = matrix_image[i][j];
            }
        }
    }
    return val_min;
}


int max(int **matrix_image, int rows, int columns){
    int val_max = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (val_max < matrix_image[i][j])
            {
                val_max = matrix_image[i][j];
            }
        }
    }
    return val_max;
}

int** contrast_linear_T(int **matrix_image, int rows, int columns){
    int min_val = min(matrix_image, rows, columns), max_val = max(matrix_image, rows, columns);
    int **matrix_image_modified = (int **)malloc(rows * sizeof(int *));
    if (matrix_image_modified == NULL)
    {
        printf("Erreur lors de l'allocation de l'espace matrice_image!");
        exit(1);
    }
    for (int i = 0; i < rows; i++)
    {
        matrix_image_modified[i] = (int *)malloc(columns * sizeof(int));
        if (matrix_image[i] == NULL)
        {
            printf("Erreur lors de l'allocation de l'espace sous tableau matrice_image!");
            exit(1);
        }
    }
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            matrix_image_modified[i][j] = 255 * (matrix_image[i][j] - min_val) / (max_val - min_val);
        }
    }
    return matrix_image_modified;
}

