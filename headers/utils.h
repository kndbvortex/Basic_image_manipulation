#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#define IMAGE_INPUT_FOLDER "images/input/"
#define IMAGE_OUTPUT_FOLDER "images/output/"

void printArray(int *array, int lenght);
void printMatrix(int **matrix, int rows, int columns);
void printFloatArray(float *array, int lenght);
void printFloatMatrix(float **matrix, int rows, int columns);

int *allocateVector(int size);
int **allocateMatrix(int rows, int columns);
float **allocateFloatMatrix(int rows, int columns);

int **readImage(char filename[], int *rows, int *columns);
void writeImage(char filename[], int **matrix_image, int rows, int columns);
void writeHistogram(int hist[], int m);

void finTache(char tache_name[]);

int **readFilter(char filename[], int *row, int *col);
float **readFloatFilter(char filename[], int *row, int *col);

int min_vector(int *v, int taille);
int indice_min_vector(int *v, int taille);
void init_vector(int *v, int taille, int val);
int puissance_2_suivante(int nbre);
#endif