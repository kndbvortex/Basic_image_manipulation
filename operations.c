#include <stdio.h>
#include <math.h>

#include "headers/operations.h"
#include "headers/utils.h"

int *hist(int **matrix_image, int rows, int columns)
{
    int *hist = malloc(256 * sizeof(int));

    if (hist == NULL)
    {
        printf("Erreur lors de l'allocation de hist!");
        exit(1);
    }
    for (int i = 0; i < 256; i++)
        hist[i] = 0;

    printf("%d\n", rows);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            hist[matrix_image[i][j]]++;
        }
    }
    return hist;
}

double *hist_normalise(int **matrix_image, int rows, int columns)
{
    int *hist_val = hist(matrix_image, rows, columns);
    double *hist_norm = malloc(256 * sizeof(double));

    if (hist_norm == NULL)
    {
        printf("Erreur lors de l'allocation de hist!");
        exit(1);
    }
    hist_norm[0] = (double)hist_val[0] / (rows * columns);
    for (int i = 1; i < 256; i++)
        hist_norm[i] = (double)hist_val[i] / (rows * columns) + hist_norm[i - 1];

    return hist_norm;
}

double luminance(int **matrix_image, int rows, int columns)
{
    double L = 0.0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            L += matrix_image[i][j];
        }
    }
    L /= (rows * columns);
    return L;
}

int **seuillage(int **matrix_image, int rows, int columns, int seuil)
{
    if ((seuil >= 256 || seuil < 0))
    {
        printf("Seuil non valide\n");
        exit(EXIT_FAILURE);
    }
    int **matrix_bin = allocateMatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (matrix_image[i][j] < seuil)
            {
                matrix_bin[i][j] = 0;
            }
            else
            {
                matrix_bin[i][j] = 255;
            }
        }
    }
    return matrix_bin;
}

int min(int **matrix_image, int rows, int columns)
{
    float val_min = INFINITY;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (val_min > matrix_image[i][j])
            {
                val_min = matrix_image[i][j];
            }
        }
    }
    return (int)val_min;
}

int max(int **matrix_image, int rows, int columns)
{
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

int **contrast_linear_T(int **matrix_image, int rows, int columns)
{
    int min_val = min(matrix_image, rows, columns), max_val = max(matrix_image, rows, columns);
    int **matrix_image_modified = allocateMatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix_image_modified[i][j] = 255 * (matrix_image[i][j] - min_val) / (max_val - min_val);
        }
    }
    return matrix_image_modified;
}

// Min-max par morceau
int **contrast_linear_avec_saturation(int **matrix_image, int rows, int columns, int smin, int smax)
{
    int min_val = min(matrix_image, rows, columns), max_val = max(matrix_image, rows, columns);
    if (smin >= min_val)
    {
        min_val = smin;
    }
    if (smax <= max_val)
    {
        max_val = smax;
    }
    int **matrix_image_modified = allocateMatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix_image_modified[i][j] = 255 * (matrix_image[i][j] - min_val) / (max_val - min_val);
            if (matrix_image_modified[i][j] < 0)
            {
                matrix_image_modified[i][j] = 0;
            }
            else if (matrix_image_modified[i][j] > 255)
            {
                matrix_image_modified[i][j] = 255;
            }
        }
    }
    return matrix_image_modified;
}

// Inversion de l'image(Remplacer chaque valeur m[i, j] par -m[i, j]+255)
int **inverseImage(int **matrix_image, int rows, int columns)
{
    int **matrix_image_modified = allocateMatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix_image_modified[i][j] = 255 - matrix_image[i][j];
        }
    }
    return matrix_image_modified;
}

// Égalisation d'histogramme:
// On part de la construction de l'histogramme puis on construit l'hhistogramme
// cummulé on normalise cette cumulation et enfin on attribut à chaque pixel
// sa fréquence cumulé ramené à l'intervale [0, 255]
int **egalisationHistogram(int **matrix_image, int rows, int columns)
{
    int *hist_val = hist(matrix_image, rows, columns);
    double *fraction_pixel = malloc(256 * sizeof(double));

    if (fraction_pixel == NULL)
    {
        printf("Erreur lors de l'allocation de des fractions!");
        exit(1);
    }
    int **matrix_egalise = allocateMatrix(rows, columns);

    for (int i = 0; i < 256; i++)
        fraction_pixel[i] = (double)hist_val[i] / (rows * columns);

    for (int i = 1; i <= 256; i++)
    {
        fraction_pixel[i] += fraction_pixel[i - 1];
    }
    // printArray(hist_val);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix_egalise[i][j] = fraction_pixel[matrix_image[i][j]] * 255;
        }
    }
    return matrix_egalise;
}

// S = l.r, 0 <= r < a
// S = m.(r-a) + v, a <= r < b
// S = n.(r-b) + w, b <= r < L-1
// where l, m, n are slopes
// int **transformation_lineaire_par_morceau(int **matrix_image, int rows, int columns, double coef_dir[], int cord_ord[], int seuils[], int n)
// {
//     int **matrix_image_trans = allocateMatrix(rows, columns);
//     for (int i = 0; i < rows; i++)
//     {
//         for (int j = 0; j < columns; j++)
//         {
//             if (matrix_image[i][j] >= 0 && matrix_image[i][j] < seuils[0]){
//                 matrix_image_trans[i][j] = coef_dir[0] * matrix_image[i][j];
//             }
//             else{
//                 int last = 0;
//                 int k=1;
//                 while(last==0 || k < n)
//                 {
//                     if (matrix_image[i][j] < seuils[k] && matrix_image[i][j] > seuils[k - 1])
//                     {
//                         matrix_image_trans[i][j] = coef_dir[k] * (matrix_image[i][j] - seuils[k - 1]) + cord_ord[k];
//                         last = 1;
//                     }
//                     k++;
//                 }
//                 if(last == 1){
//                     if (matrix_image[i][j] >= seuils[k-1] && matrix_image[i][j] < 255)
//                     {
//                         matrix_image_trans[i][j] = coef_dir[k] * (matrix_image[i][j] - seuils[k - 1]) + cord_ord[k];
//                     }
//                 }
//             }
                
//         }
//     }
//     writeImage("images/morceau.pgm", matrix_image_trans, rows, columns);
//     return matrix_image_trans;
// }

// Incompréhension ?????
int **transformation_par_log(int **matrix_image, int rows, int columns)
{
    double *hist_norm = hist_normalise(matrix_image, rows, columns);
    int **matrix_image_trans = allocateMatrix(rows, columns);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix_image_trans[i][j] = 255 * pow(matrix_image[i][j] / (double)255, 5);
            printf("%lf; ", hist_norm[matrix_image[i][j]]);
        }
    }
    writeImage("images/log.pgm", matrix_image_trans, rows, columns);
    return matrix_image_trans;
}

int **rogner(int **matrix_image, int rows, int columns, int new_row, int new_columns)
{
    if(new_columns<=0 || new_row<=0)
    {
        printf("Mauvaise dimension de rognage\n !!!");
        exit(EXIT_FAILURE);
    }
    if(rows <= new_row && columns <= new_columns)
    {
        return matrix_image;
    }
    int **result_matrix = allocateMatrix(new_row, new_columns);
    for(int i=0; i<new_row; i++){
        for(int j=0; j<new_columns; j++){
            result_matrix[i][j] = matrix_image[i][j];
        }
    }
    return result_matrix;
}

int **OULogique(int **matrix_image, int row1, int col1, int **bin_matrix, int row2, int col2){
    bin_matrix = seuillage(bin_matrix, row2, col2, 127);
    int min_row=row1, min_col=col1;
    if(min_row > row2)
        min_row = row2;
    if(min_col > col2)
        min_col = col2;

    int **ou_matrix = allocateMatrix(min_row, min_col);
    for(int i=0; i<min_row; i++){
        for(int j=0; j<min_col; j++){
            if (bin_matrix[i][j] == 255)
                ou_matrix[i][j] = 255;
            else
                ou_matrix[i][j] = matrix_image[i][j];
        }   
    }
    
    writeImage("images/output/testOU.pgm", ou_matrix, min_row, min_col);

    return ou_matrix;
}
int **ETLogique(int **matrix_image, int row1, int col1, int **bin_matrix, int row2, int col2)
{
    bin_matrix = seuillage(bin_matrix, row2, col2, 127);
    int min_row = row1, min_col = col1;
    if (min_row > row2)
        min_row = row2;
    if (min_col > col2)
        min_col = col2;

    int **et_matrix = allocateMatrix(min_row, min_col);
    for (int i = 0; i < min_row; i++)
    {
        for (int j = 0; j < min_col; j++)
        {
            if(bin_matrix[i][j] == 0)
                et_matrix[i][j] = 0;
            else
                et_matrix[i][j] = matrix_image[i][j];
        }
    }

    writeImage("images/output/testET.pgm", et_matrix, min_row, min_col);

    return et_matrix;
}