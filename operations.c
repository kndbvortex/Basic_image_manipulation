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

int seuil_otsu(int **matrix_image, int rows, int columns)
{
    int min_pixel = 0;
    float moy1, moy2, p1, p2, min = 0;
    int *h = hist(matrix_image, rows, columns);
    for (int T = 0; T < 256; T++)
    {
        moy1 = 0;
        moy2 = 0;
        p1 = 0;
        p2 = 0;
        // Calcul des moyennes
        for (int i = 0; i <= T - 1; i++)
            p1 += h[i];

        for (int i = T; i <= 255; i++)
            p2 += h[i];

        p1 /= (rows * columns);
        p2 /= (rows * columns);

        for (int i = 0; i <= T - 1; i++)
            moy1 += i * h[i];

        for (int i = T; i <= 255; i++)
            moy2 += i * h[i];

        moy1 /= p1;
        moy2 /= p2;
        float var = p1 * p2 * (moy1 - moy2) * (moy1 - moy2);

        if (var > min)
        {
            min = var;
            min_pixel = T;
        }
    }
    free(h);
    return min_pixel;
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
    finTache("Transformation linéaire");
    writeImage("images/output/transformationLineaire.pgm", matrix_image_modified, rows, columns);
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
    finTache("Transformation linéaire avec saturation");
    writeImage("images/output/transformationLineaireSaturation.pgm", matrix_image_modified, rows, columns);
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
    finTache("Inverse de l'image");
    writeImage("images/output/Inverse.pgm", matrix_image_modified, rows, columns);
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
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix_egalise[i][j] = fraction_pixel[matrix_image[i][j]] * 255;
        }
    }
    finTache("Egalisation d'histogramme");
    writeImage("images/output/egalise.pgm", matrix_egalise, rows, columns);
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
    if (new_columns <= 0 || new_row <= 0)
    {
        printf("Mauvaise dimension de rognage\n !!!");
        exit(EXIT_FAILURE);
    }
    if (rows <= new_row && columns <= new_columns)
    {
        return matrix_image;
    }
    int **result_matrix = allocateMatrix(new_row, new_columns);
    for (int i = 0; i < new_row; i++)
    {
        for (int j = 0; j < new_columns; j++)
        {
            result_matrix[i][j] = matrix_image[i][j];
        }
    }
    return result_matrix;
}

int **OULogique(int **matrix_image, int row1, int col1, int **bin_matrix, int row2, int col2)
{
    bin_matrix = seuillage(bin_matrix, row2, col2, 127);
    int min_row = row1, min_col = col1;
    if (min_row > row2)
        min_row = row2;
    if (min_col > col2)
        min_col = col2;

    int **ou_matrix = allocateMatrix(min_row, min_col);
    for (int i = 0; i < min_row; i++)
    {
        for (int j = 0; j < min_col; j++)
        {
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
            if (bin_matrix[i][j] == 0)
                et_matrix[i][j] = 0;
            else
                et_matrix[i][j] = matrix_image[i][j];
        }
    }

    writeImage("images/output/testET.pgm", et_matrix, min_row, min_col);

    return et_matrix;
}

int **XORLogique(int **bin_image, int row1, int col1, int **bin_image2, int row2, int col2)
{
    bin_image = seuillage(bin_image, row1, col1, 127);
    bin_image2 = seuillage(bin_image2, row2, col2, 127);
    int min_row = row1, min_col = col1;
    if (min_row > row2)
        min_row = row2;
    if (min_col > col2)
        min_col = col2;
    int **xor_matrix = allocateMatrix(min_row, min_col);
    for (int i = 0; i < min_row; i++)
    {
        for (int j = 0; j < min_col; j++)
        {
            if (bin_image[i][j] != bin_image2[i][j])
            {
                xor_matrix[i][j] = 0;
            }
            else
            {
                xor_matrix[i][j] = 255;
            }
        }
    }
    finTache("XOR");
    writeImage("images/output/xorImage.pgm", xor_matrix, min_row, min_col);
    return xor_matrix;
}

int **addition(int **matrix_image, int row1, int col1, int **matrix_image2, int row2, int col2)
{
    int min_row = row1, min_col = col1;
    if (min_row > row2)
    {
        min_row = row2;
    }

    if (min_col > col2)
    {
        min_col = col2;
    }

    int **result_matrix = allocateMatrix(min_row, min_col);

    for (int i = 0; i < min_row; i++)
    {
        for (int j = 0; j < min_col; j++)
        {
            result_matrix[i][j] = matrix_image[i][j] + matrix_image2[i][j];
            if (result_matrix[i][j] > 255)
            {
                result_matrix[i][j] = 255;
            }
        }
    }

    finTache("Addition des images");
    writeImage("images/output/Addition.pgm", result_matrix, min_row, min_col);
    return result_matrix;
}
int **soustraction(int **matrix_image, int row1, int col1, int **matrix_image2, int row2, int col2)
{
    int min_row = row1, min_col = col1;
    if (min_row > row2)
    {
        min_row = row2;
    }

    if (min_col > col2)
    {
        min_col = col2;
    }

    int **result_matrix = allocateMatrix(min_row, min_col);

    for (int i = 0; i < min_row; i++)
    {
        for (int j = 0; j < min_col; j++)
        {
            result_matrix[i][j] = matrix_image[i][j] - matrix_image2[i][j];
            if (result_matrix[i][j] < 0)
            {
                result_matrix[i][j] = 0;
            }
        }
    }

    finTache("Soustraction des images");
    writeImage("images/output/Suppression.pgm", result_matrix, min_row, min_col);
    return result_matrix;
}
int **multiplication(int **matrix_image, int row1, int col1, float ratio)
{

    if (ratio <= 0)
    {
        printf("Entrez un ratio > 0");
        exit(EXIT_FAILURE);
    }

    int **result_matrix = allocateMatrix(row1, col1);

    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col1; j++)
        {
            result_matrix[i][j] = ratio * matrix_image[i][j];
            if (result_matrix[i][j] > 255)
            {
                result_matrix[i][j] = 255;
            }
        }
    }

    finTache("Multiplication des images");
    writeImage("images/output/Multiplication.pgm", result_matrix, row1, col1);
    return result_matrix;
}

// Zoom ou dézoomer une image
int **ratioImage(int **matrix_image, int row, int col, int new_row, int new_col)
{
    if (new_row <= 0 || new_col <= 0)
    {
        printf("Les nouvelles dimensions ne sont pas >0");
        exit(EXIT_FAILURE);
    }
    int **result = allocateMatrix(new_row, new_col);
    for (int i = 0; i < new_row; i++)
        for (int j = 0; j < new_col; j++)
            result[i][j] = -1;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            result[(int)(i * ((float)new_row / row))][(int)(j * (float)new_col / col)] = matrix_image[i][j];
        }
    }
    return result;
}

void interpolationSimple(int **matrix_image, int row, int col, int new_row, int new_col)
{
    int **result = ratioImage(matrix_image, row, col, new_row, new_col);

    for (int i = 0; i < new_row; i++)
    {
        for (int j = 0; j < new_col; j++)
        {
            if (result[i][j] == -1)
                result[i][j] = matrix_image[(int)(i / ((float)new_row / row))][(int)(j / ((float)new_col / col))];
        }
    }
    finTache("Interpolation Simple");
    writeImage("images/output/interpolation.pgm", result, new_row, new_col);
}

void interpolationBilineaire(int **matrix_image, int row, int col, int new_row, int new_col)
{
    int **result = ratioImage(matrix_image, row, col, new_row, new_col);

    for (int i = 0; i < new_row; i++)
    {
        for (int j = 0; j < new_col; j++)
        {
            if (result[i][j] == -1)
            {
                int index_i = (int)(i / ((float)new_row / row));
                int index_j = (int)(j / ((float)new_col / col));
                result[i][j] = matrix_image[index_i][index_j];
                if (index_i > 0)
                {
                    if (index_j < col - 1)
                    {
                        result[i][j] += matrix_image[index_i - 1][index_j];
                        result[i][j] += matrix_image[index_i - 1][index_j + 1];
                        result[i][j] += matrix_image[index_i][index_j + 1];
                    }
                    else
                    {
                        result[i][j] += matrix_image[index_i - 1][index_j];
                        result[i][j] += matrix_image[index_i - 1][index_j - 1];
                        result[i][j] += matrix_image[index_i][index_j - 1];
                    }
                }
                else
                {
                    if (index_j < col - 1)
                    {
                        result[i][j] += matrix_image[index_i + 1][index_j];
                        result[i][j] += matrix_image[index_i + 1][index_j + 1];
                        result[i][j] += matrix_image[index_i][index_j + 1];
                    }
                    else
                    {
                        result[i][j] += matrix_image[index_i + 1][index_j];
                        result[i][j] += matrix_image[index_i + 1][index_j - 1];
                        result[i][j] += matrix_image[index_i][index_j - 1];
                    }
                }

                result[i][j] /= 4;
            }
        }
    }
    finTache("Interpolation Bilinéaire");
    writeImage("images/output/interpolationBiléaire.pgm", result, new_row, new_col);
}

void interpolationBicubique(int **matrix_image, int row, int col, int new_row, int new_col)
{
    int **result = ratioImage(matrix_image, row, col, new_row, new_col);

    for (int i = 0; i < new_row; i++)
    {
        for (int j = 0; j < new_col; j++)
        {
            if (result[i][j] == -1)
            {
                int index_i = (int)(i / ((float)new_row / row));
                int index_j = (int)(j / ((float)new_col / col));
                result[i][j] = 0;
                if (index_i > 2)
                {
                    if (index_j < col - 3)
                    {
                        for (int k = index_i; k > index_i - 4; k--)
                        {
                            for (int l = index_j; l < index_j + 4; l++)
                            {
                                result[i][j] += matrix_image[k][l];
                            }
                        }
                    }
                    else
                    {
                        for (int k = index_i; k > index_i - 4; k--)
                        {
                            for (int l = index_j; l > index_j - 4; l--)
                            {
                                result[i][j] += matrix_image[k][l];
                            }
                        }
                    }
                }
                else
                {
                    if (index_j < col - 3)
                    {
                        for (int k = index_i; k < index_i + 4; k++)
                        {
                            for (int l = index_j; l < index_j + 4; l++)
                            {
                                result[i][j] += matrix_image[k][l];
                            }
                        }
                    }
                    else
                    {
                        for (int k = index_i; k < index_i + 4; k++)
                        {
                            for (int l = index_j; l > index_j - 4; l--)
                            {
                                result[i][j] += matrix_image[k][l];
                            }
                        }
                    }
                }

                result[i][j] /= 16;
            }
        }
    }
    finTache("Interpolation Bicubique");
    writeImage("images/output/interpolationBicubique.pgm", result, new_row, new_col);
}

void rotation(int **matrix_image, int row, int col, float angle)
{
    float rad_angle = 3.14 * angle / 180;
    int diagonal = sqrt(row * row + col * col);
    int **result = allocateMatrix(diagonal, diagonal);

    for (int i = 0; i < diagonal; i++)
        for (int j = 0; j < diagonal; j++)
            result[i][j] = -1;

    int alpha = 0, beta = 0;

    if (cos(rad_angle) > 0 && sin(rad_angle) > 0)
        alpha = abs(cos(3.14 / 2 - rad_angle) * col);
    else if (cos(rad_angle) > 0 && sin(rad_angle) < 0)
        beta = abs(sin(rad_angle) * row);
    else if (cos(rad_angle) < 0 && sin(rad_angle) > 0)
    {
        alpha = (1.2) * row;
        beta = sin(rad_angle) * col;
    }
    else
    {
        beta = diagonal * abs(sin(3.14 / 4 + rad_angle));
        alpha = abs(sin(rad_angle)) * col;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            // Rotation du point (i, j) en (x, y) l'image de (i, j)
            int x = (int)((i)*cos(rad_angle) + (j)*sin(rad_angle)) + beta;
            int y = (int)(-1 * (i)*sin(rad_angle) + (j)*cos(rad_angle)) + alpha;
            if (x >= 0 && y >= 0 && x < diagonal && y < diagonal)
                result[x][y] = matrix_image[i][j];
        }
    }

    for (int i = 0; i < diagonal; i++)
    {
        for (int j = 0; j < diagonal; j++)
        {
            if (result[i][j] == -1)
            {
                // Recherche de l'antécédent
                int x = (int)((i - beta) * cos(rad_angle) - (j - alpha) * sin(rad_angle));
                int y = (int)((i - beta) * sin(rad_angle) + (j - alpha) * cos(rad_angle));

                if (x < 0 || y < 0)
                    result[i][j] = 0;
                else if (x >= row || y >= col)
                    result[i][j] = 0;
                else
                {
                    result[i][j] = matrix_image[x][y];
                }
            }
        }
    }

    finTache("Rotation de l'image");
    writeImage("images/output/rotation.pgm", result, diagonal, diagonal);
}