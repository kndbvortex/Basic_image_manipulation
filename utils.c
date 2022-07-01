#include <stdio.h>
#include <stdlib.h>
#include "headers/utils.h"
#include <string.h>
#include <math.h>

void printArray(int *array, int lenght)
{
    printf("[");
    for (int i = 0; i < lenght; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("]\n");
}

void printFloatArray(float *array, int lenght)
{
    printf("[");
    for (int i = 0; i < lenght; i++)
    {
        printf("%f, ", array[i]);
    }
    printf("]\n");
}

void printFloatMatrix(float **matrix, int rows, int columns)
{
    printf("[\n");
    for (int i = 0; i < rows; i++)
    {
        printf("  ");
        printFloatArray(matrix[i], columns);
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

int *allocateVector(int size)
{
    int *v = NULL;
    v = malloc(size * sizeof(int));
    if (v == NULL)
    {
        printf("Error Lors de l'allocation du vecteur");
        exit(EXIT_FAILURE);
    }
    return v;
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
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

float **allocateFloatMatrix(int rows, int columns)
{
    float **matrix = (float **)malloc(rows * sizeof(float *));
    if (matrix == NULL)
    {
        printf("Erreur lors de l'allocation de l'espace matrice_image!");
        exit(1);
    }
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (float *)malloc(columns * sizeof(float));
        if (matrix[i] == NULL)
        {
            printf("Erreur lors de l'allocation de l'espace sous tableau matrice_image!");
            exit(EXIT_FAILURE);
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
        printf("Erreur lors de l'ouverture du fichier {%s} n'existe pas!", filename);
        exit(EXIT_FAILURE);
    }
    else
    {
        char text[255];
        int val_max_color = 0, col_num = 0;
        fscanf(fptr, "%s\n", text);
        fscanf(fptr, "%[^\n]", text);
        fscanf(fptr, "%d %d\n", columns, rows);
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
                    exit(EXIT_FAILURE);
                }
            }
        }

        fclose(fptr);
        printf("L'image {%s} a été lu avec succès, de dimension %d X %d\n", filename, *rows, *columns);
        return matrix_image;
    }
}

/* Create image with a given matrix */
void writeImage(char filename[], int **matrix_image, int rows, int columns)
{
    printf("Début de la création du fichier ...\n");
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

    printf("Sauvegarde effectuée avec succès sous {%s}\n", filename);
    fclose(fptr);
    char command[1000] = "eog ";
    strcat(command, filename);
    system(command);
}

void finTache(char tache_name[])
{
    printf("Fin de l'opération %s\n", tache_name);
}

void writeHistogram(int hist[], int m)
{
    int **result = allocateMatrix(m, 256);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < 256; j++)
            result[i][j] = 0;
    for (int j = 0; j < 256; j++)
    {
        for (int i = m - 1; i >= m-hist[j]; i--)
            result[i][j] = 255;
    }
    writeImage("images/output/histogram.pgm", result, m, 256);
}

int **readFilter(char filename[], int *row, int *col)
{
    FILE *fptr;

    fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier {%s} n'existe pas!", filename);
        exit(EXIT_FAILURE);
    }
    else
    {
        fscanf(fptr, "%d %d\n", col, row);
        int **filtre = allocateMatrix(*row, *col);
        for (int i = 0; i < *row; i++)
        {
            for (int j = 0; j < *col; j++)
            {
                fscanf(fptr, "%d ", &filtre[i][j]);
            }
            fscanf(fptr, "\n");
        }
        fclose(fptr);
        return filtre;
    }
}

float **readFloatFilter(char filename[], int *row, int *col)
{
    FILE *fptr;

    fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier {%s} n'existe pas!", filename);
        exit(EXIT_FAILURE);
    }
    else
    {
        fscanf(fptr, "%d %d\n", col, row);
        float **filtre = allocateFloatMatrix(*row, *col);
        for (int i = 0; i < *row; i++)
        {
            for (int j = 0; j < *col; j++)
            {
                fscanf(fptr, "%f ", &filtre[i][j]);
            }
            fscanf(fptr, "\n");
        }

        fclose(fptr);
        return filtre;
    }
}

int min_vector(int *v, int taille)
{
    float val_min = INFINITY;
    for (int i = 0; i < taille; i++)
    {
        if (val_min > v[i])
        {
            val_min = v[i];
        }
    }
    return (int)val_min;
}

int indice_min_vector(int *v, int taille)
{
    float val_min = INFINITY, indice;
    for (int i = 0; i < taille; i++)
    {
        if (val_min > v[i])
        {
            val_min = v[i];
            indice = i;
        }
    }
    return (int)indice;
}

void init_vector(int *v, int taille, int val)
{
    for (int i = 0; i < taille; i++)
    {
        v[i] = val;
    }
}

int puissance_2_suivante(int nbre)
{
    int b = nbre;
    while ((int)log2(b) != log2(b))
        b++;
    return b;
}