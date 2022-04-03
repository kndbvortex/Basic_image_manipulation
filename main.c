#include <stdlib.h>
#include <stdio.h>

#include "headers/operations.h"

int** readImage(char filename[], int *rows, int *columns);
void writeImage(char filename[], int **matrix_image, int rows, int columns);

void printArray(int *array, int lenght){
    printf("[");
    for (int i=0; i<=lenght; i++){
        printf("%d, ",array[i]);
    }
    printf("]\n");
}

void printMatrix(int** matrix, int rows, int columns){
    printf("[\n");
    for(int i=0; i<rows; i++){
        printf("  ");
        printArray(matrix[i], columns);
    }
    printf("]\n");
}

int ** readImage(char filename[], int *rows, int *columns)
{
    FILE *fptr;

    fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier!");
        exit(1);
    }
    else{
        char text[255];
        fscanf(fptr, "%s\n", text);
        fscanf(fptr, "%[^\n]", text);
        fscanf(fptr, "%d %d\n", columns, rows);
        printf("%d %d\n", *columns, *rows);
        int** matrix_image = (int **)malloc(*rows * sizeof(int *));
        if (matrix_image == NULL){
            printf("Erreur lors de l'allocation de l'espace matrice_image!");
            exit(1);
        }
        for (int i = 0; i < *rows; i++)
        {
            matrix_image[i] = (int *)malloc(*columns * sizeof(int));
            if (matrix_image[i] == NULL){
                printf("Erreur lors de l'allocation de l'espace sous tableau matrice_image!");
                exit(1);
            }
        }
        for (int i = 0; i < *rows; i++)
        {
            for (int j = 0; j < *columns; j++)
            {
                fscanf(fptr, "%d\n", &matrix_image[i][j]);
            }
        }
        // printMatrix(matrix_image, *rows, *columns);

        fclose(fptr);
        return matrix_image;
    }

}

/* Create image with a given matrix */
void writeImage(char filename[], int **matrix_image, int rows, int columns){
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier!");
        exit(1);
    }
    else{
        fprintf(fptr, "P2\n#Created by Durande Kamga\n");
        fprintf(fptr, "%d %d\n", columns, rows);
        for(int i=0; i<rows; i++){
            for (int j=0; j<columns; j++){
                fprintf(fptr, "%d\n", matrix_image[i][j]);
            }
        }
    }
    printf("Sauvegarde effectué avec succès\n");
    fclose(fptr);
}

int main(int argc, char* argv[]){
    int *hist_value = malloc(255*sizeof(int));
    if(hist_value == NULL){
        printf("Erreur lors de l'allocation de hist!");
        exit(1);
    }
    for(int i=0; i<255; i++)
        hist_value[i] = 0;

    int rows=0, columns=0;
    int** matrix_image = readImage("images/bateau.pgm", &rows, &columns);
    // hist(matrix_image, rows, columns, hist_value);
    // printArray(hist_value, 255);
    // printf("min: %d, max: %d", min(matrix_image, rows, columns), max(matrix_image, rows, columns));
    int **contrast = contrast_linear_T(matrix_image, rows, columns);
    writeImage("images/testcontrast.pgm", contrast, rows, columns);
    return 0;
}