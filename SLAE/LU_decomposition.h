#include <stdio.h>
#include <vector>
#include <iostream>

namespace SLAE
{
    void LUDecompose(std::vector<std::vector<double>> matrix, std::vector<std::vector<double>> &L, std::vector<std::vector<double>> &U, int n)
    {
        int length = n;
//        L = std::vector<std::vector<double>>(length);
//        U = std::vector<std::vector<double>>(length);
//        for (int i = 0; i < length; i++)
//        {
//            L[i] = std::vector<double>(length, 0);
//            U[i] = std::vector<double>(length, 0);
//        }

        for (int j = 0; j < length; j++)
        {
            U[0][j] = matrix[0][j];
            L[j][0] = matrix[j][0] / U[0][0];
        }

        for (int i = 1; i < length; i++)
        {
            for (int j = i; j < length; j++)
            {
                double sum = 0.0;
                for (int k = 0; k < i; k++)
                {
                    sum += L[i][k] * U[k][j];
                }

                U[i][j] = matrix[i][j] - sum;
            }

            for (int j = i; j < length; j++)
            {
                double sum = 0.0;
                for (int k = 0; k < i; k++)
                {
                    sum += L[j][k] * U[k][i];
                }

                L[j][i] = (matrix[j][i] - sum) / U[i][i];
            }
        }
    }

    std::vector<double> Solve_LU(std::vector<std::vector<double>> matrix, std::vector<double> b, int n)
    {
        int length = n;
        // LUDecompose(matrix, std::vector<std::vector<double>> L, std::vector<std::vector<double>> U, int n);
        std::vector<std::vector<double>> L = std::vector<std::vector<double>>(length);
        std::vector<std::vector<double>> U = std::vector<std::vector<double>>(length);
        for (int i = 0; i < length; i++)
        {
            L[i] = std::vector<double>(length, 0);
            U[i] = std::vector<double>(length, 0);
        }
        LUDecompose(matrix, L, U, n);

        std::vector<double> y = std::vector<double>(length, 0);
        for (int i = 0; i < length; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
            {
                sum += L[i][j] * y[j];
            }
            y[i] = b[i] - sum;
        }

        std::vector<double> x = std::vector<double>(length, 0);
        for (int i = length - 1; i >= 0; i--)
        {
            double sum = 0.0;
            for (int j = i + 1; j < length; j++)
            {
                sum += U[i][j] * x[j];
            }
            x[i] = (y[i] - sum) / U[i][i];
        }
        return x;
    }
}
