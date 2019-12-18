#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>

namespace SLAE
{
    double GaussSeidelMethod(double eps = 0.00001)
    {
        return eps;
    }

    bool Converge(std::vector<double> xk, std::vector<double> xkp, int n)
    {
        int length = n;

        double norm = 0.0;
        for (int i = 0; i < length; i++)
        {
            norm += (xk[i] - xkp[i]) * (xk[i] - xkp[i]);
        }

        return sqrt(norm) < GaussSeidelMethod(0.00001);
    }

    std::vector<double> Solve_GaussSeidel(std::vector<std::vector<double>> matrix, std::vector<double> b, int n)
    {
        int length = n;
        std::vector<double> p = std::vector<double>(length, 0);
        std::vector<double> x = std::vector<double>(length, 0);

        do
        {
            p = std::vector<double>(x.begin(), x.begin() + length);

            for (int i = 0; i < length; i++)
            {
                double var = 0.0;
                for (int j = 0; j < i; j++)
                {
                    var += matrix[i][j] * x[j];
                }
                for (int j = i + 1; j < length; j++)
                {
                    var += matrix[i][j] * p[j];
                }
                x[i] = (b[i] - var) / matrix[i][i];
            }

        } while (!Converge(x, p, n));
        return x;
    }
}

