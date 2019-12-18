#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

namespace SLAE
{
    std::vector<std::vector<double>> GenerateMatrix(int size)
    {
        std::vector<std::vector<double>> matrix;
        matrix = std::vector<std::vector<double>>(size);
        for (int i = 0; i < size; i++)
            matrix[i] = std::vector<double>(size, 0);

        for (int i = 0; i < size; i++)
        {
            double sum = 0.0;
            for (int j = 0; j < size; j++)
            {
                matrix[i][j] = rand() % 10 + (-10);
                sum += abs(matrix[i][j]);
            }

            matrix[i][i] = sum + rand() % 10;
        }

        return matrix;
    }

    std::vector<double> GenerateVector(int size)
    {
        std::vector<double> b = std::vector<double>(size, 0);

        for (int i = 0; i < size; i++)
        {
            b[i] = rand() % 10 + (-10);
        }

        return b;
    }
}
