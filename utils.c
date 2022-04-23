#include <stdio.h>
#include <stdlib.h>
#include "headers/utils.h"

void printArray(int *array, int lenght)
{
    printf("[");
    for (int i = 0; i <= lenght; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("]\n");
}

void printMatrix(int **matrix, int rows, int columns)
{
    printf("[\n");
    for (int i = 0; i < rows; i++)
    {
        printf("  ");
        printArray(matrix[i], columns);
    }
    printf("]\n");
}

int **allocateMatrix(int rows, int columns)
{
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL)
    {
        printf("Erreur lors de l'allocation de l'espace matrice_image!");
        exit(1);
    }
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(columns * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Erreur lors de l'allocation de l'espace sous tableau matrice_image!");
            exit(1);
        }
    }
    return matrix;
}

int **readImage(char filename[], int *rows, int *columns)
{
    FILE *fptr;

    fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier!");
        exit(1);
    }
    else
    {
        char text[255];
        int val_max_color = 0, col_num = 0;
        fscanf(fptr, "%s\n", text);
        fscanf(fptr, "%[^\n]", text);
        fscanf(fptr, "%d %d\n", columns, rows);
        printf("%d %d\n", *columns, *rows);
        fscanf(fptr, "%d\n", &val_max_color);

        int **matrix_image = allocateMatrix(*rows, *columns);
        for (int i = 0; i < *rows; i++)
        {
            for (int j = 0; j < *columns; j++)
            {
                fscanf(fptr, "%d\n", &col_num);
                if (col_num <= val_max_color && col_num >= 0)
                {
                    matrix_image[i][j] = col_num;
                }
                else
                {
                    exit(1);
                }
            }
        }
        // printMatrix(matrix_image, *rows, *columns);

        fclose(fptr);
        return matrix_image;
    }
}

/* Create image with a given matrix */
void writeImage(char filename[], int **matrix_image, int rows, int columns)
{
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier!");
        exit(1);
    }
    else
    {
        fprintf(fptr, "P2\n#Created by Durande Kamga\n");
        fprintf(fptr, "%d %d\n255\n", columns, rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                fprintf(fptr, "%d\n", matrix_image[i][j]);
            }
        }
    }
    printf("Sauvegarde effectué avec succès\n");
    fclose(fptr);
}