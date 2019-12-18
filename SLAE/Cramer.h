#include "SLAE.h"
#include <stdio.h>
#include <vector>
#include <iostream>

namespace SLAE
{
    double Determinant(std::vector<std::vector<double>> matrix, int n);
    std::vector<double> Solve_Cramer(std::vector<std::vector<double>> matrix, std::vector<double> b, int n)
    {
        int length = n;
        double detMatrix = Determinant(matrix, n);
        std::vector<double> x = std::vector<double>(length, 0);

        for (int i = 0; i < length; i++)
        {
            std::vector<std::vector<double>> newMatrix = std::vector<std::vector<double>>(length);
            for (int i = 0; i < length; i++)
                newMatrix[i] = std::vector<double>(length, 0);
            newMatrix = std::vector<std::vector<double>>(matrix);
            for (int j = 0; j < length; j++)
            {
                newMatrix[j][i] = b[j];
            }

            x[i] = Determinant(newMatrix, n) / detMatrix;
        }
        return x;
    }

    double Determinant(std::vector<std::vector<double>> matrix, int n)
    {
        int length = n;

        for (int k = 1; k < length; k++)
        {
            for (int i = k; i < length; i++)
            {
                double coeff = matrix[i][k - 1] / matrix[k - 1][k - 1];

                for (int j = 0; j < length; j++)
                {
                    matrix[i][j] -= coeff * matrix[k - 1][j];
                }
            }
        }

        //for (int k = 0; k < length; k++)
        //{
        //    // Initialize maximum value and index for pivot
        //    int i_max = k;
        //    double v_max = matrix[i_max, k];

        //    /* find greater amplitude for pivot if any */
        //    for (int i = k + 1; i < length; i++)
        //        if (Math.Abs(matrix[i, k]) > v_max)
        //        {
        //            v_max = matrix[i, k];
        //            i_max = i;
        //        }

        //    /* Swap the greatest value row with current row */
        //    if (i_max != k)
        //        swap_row(ref matrix, k, i_max);


        //    for (int i = k + 1; i < length; i++)
        //    {
        //        /* factor f to set current row kth elemnt to 0,
        //         * and subsequently remaining kth column to 0 */
        //        double f = matrix[i, k] / matrix[k, k];

        //        /* subtract fth multiple of corresponding kth
        //           row element*/
        //        for (int j = k + 1; j < length; j++)
        //            matrix[i, j] -= matrix[k, j] * f;

        //        /* filling lower triangular matrix with zeros*/
        //        matrix[i, k] = 0;
        //    }
        //}

        double det = 1.0;
        for (int i = 0; i < length; i++)
        {
            det *= matrix[i][i];
        }

        return det;
    }

    void swap_row(std::vector<std::vector<double>> matrix, int i, int j, int n)
    {
        int length = n;
        for (int k = 0; k < length; k++)
        {
            double temp = matrix[i][k];
            matrix[i][k] = matrix[j][k];
            matrix[j][k] = temp;
        }
    }
}
