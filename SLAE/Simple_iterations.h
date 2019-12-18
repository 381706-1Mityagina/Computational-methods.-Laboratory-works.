#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

namespace SLAE
{
    double SimpleIterationMethod(double eps = 0.00001)
    {
        return eps;
    }
    bool Converge_s_i(std::vector<double> xk, std::vector<double> xkp, int n)
    {
        int length = n;

        double norm = 0.0;
        for (int i = 0; i < length; i++)
        {
            norm += (xk[i] - xkp[i]) * (xk[i] - xkp[i]);
        }

        return sqrt(norm) < SimpleIterationMethod(0.00001);
    }
    std::vector<double> Solve_simple_it(std::vector<std::vector<double>> matrix, std::vector<double> b, int n)
    {
        int length = n;
        std::vector<double> p = std::vector<double>(length, 0);
        std::vector<double> x = std::vector<double>(length, 0);

        std::vector<std::vector<double>> alpha = std::vector<std::vector<double>>(length);
        for (int i = 0; i < length; i++)
            alpha[i] = std::vector<double>(length, 0);
        std::vector<double> beta = std::vector<double>(length, 0);

        for (int i = 0; i < length; i++)
        {
            beta[i] = b[i] / matrix[i][i];
            for (int j = 0; j < length; j++)
            {
                alpha[i][j] = (i != j) ? -matrix[i][j] / matrix[i][i] : 0;
            }
        }
        x = std::vector<double>(beta.begin(), beta.begin() + length);

        do
        {
            p = std::vector<double>(x.begin(), x.begin() + length);

            for (int i = 0; i < length; i++)
            {
                std::vector<double> c = std::vector<double>(length, 0);
                for (int j = 0; j < length; j++)
                {
                    c[i] += alpha[i][j] * p[j];
                }

                x[i] = beta[i] + c[i];
            }

        } while (!Converge_s_i(x, p, length));

        return x;
    }
}
