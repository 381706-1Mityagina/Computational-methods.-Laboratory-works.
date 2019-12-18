#include <stdio.h>
#include <iostream>
#include <vector>

namespace SLAE
{
    std::vector<double> Solve_Gauss(std::vector<std::vector<double>> matrix, std::vector<double> b, int n)
    {
        int length = n;
        std::vector<double> x = std::vector<double>(length, 0);

        //прямой ход решения
        for (int k = 1; k < length; k++)
        {
            for (int i = k; i < length; i++)
            {
                double coeff = matrix[i][k - 1] / matrix[k - 1][k - 1];

                for (int j = 0; j < length; j++)
                {
                    matrix[i][j] -= coeff * matrix[k - 1][j];
                }

                b[i] -= coeff * b[k - 1];
            }
        }

        //обратный ход решения
        for (int i = length - 1; i >= 0; i--)
        {
            x[i] = b[i] / matrix[i][i];

            for (int j = length - 1; j > i; j--)
            {
                x[i] -= matrix[i][j] * x[j] / matrix[i][i];
            }
        }

        return x;
    }
}
