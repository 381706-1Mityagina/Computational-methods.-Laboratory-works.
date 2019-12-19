#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <vector>
#include <time.h>
#include <complex>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <algorithm>

namespace SLAE
{
    std::vector<double> get_row(std::vector<std::vector<double>> C, int row)
    {
        int i, n;
        std::vector<double> temp;
        n = int(C.size());

        for (i=0;i<n; i++)
        {
            temp.push_back(C[row][i]);
            // cout << C[row][i] << endl;
        }
        return temp;
    }

    std::vector<double> get_cols(std::vector<std::vector<double>> C, int col)
    {
        int i, n;
        std::vector<double> temp;
        n = int(C.size());

        for (i=0;i<n; i++)
        {
            temp.push_back(C[i][col]);
        }
        return temp;
    }
    std::vector<double> Solve_sor(std::vector<std::vector<double>> ls, std::vector<double> rs, int maxit, double es, double lambda)
    {
        int n, i, iter, j, k, l;
        double sentinel = 1, mul, maxea;

        n = int(ls.size());
        std::vector<double> x = std::vector<double>(n, 0), xold = std::vector<double>(n, 0), temp = std::vector<double>(n, 0), ea = std::vector<double>(n, 0);
        std::vector<std::vector<double>> C = std::vector<std::vector<double>>(n);
        x.reserve(n);
        xold.reserve(n);
        temp.reserve(n);
        ea.reserve(n);

        C = ls;
        for (k = 0; k < n; k++)
        {
            C[k][k] = 0.0;
        }

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                // divide each val by diagonal
                C[i][j] = C[i][j] / ls[i][i];

            }
            // divide right side by diagonal
            rs[i] = rs[i] / ls[i][i];
        }

        iter = 0;

        while (sentinel == 1 && iter <= maxit)
        {
            for (int t = 0; t < n; t++)
            {
                xold[t] = x[t];
            }

            for (l = 0; l < n; l++)
            {
                temp = get_row(C,l);
                mul = std::inner_product(temp.begin(), temp.end(), x.begin(), 0.0);
                x[l] = rs[l] - mul;

                // multiply the right hand side by the relaxation
                x[l] = lambda * x[l] + (1.0 - lambda) * xold[l];
                // Checking convergence by calculating approximate error
                if (x[l] != 0)
                {
                    ea[l] = fabs((x[l] - xold[l]) / x[l]) * 100;
                }
            }
            maxea = *std::max_element(ea.begin(), ea.end());
            if (maxea <= es)
            {
                sentinel = 0;
            }
            iter = iter + 1;
        }

        return x;
    }
}
