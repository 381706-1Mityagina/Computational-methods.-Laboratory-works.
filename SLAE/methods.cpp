#include <vector>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

void rotate(std::vector<std::vector<double>> m, int N)
{
    for (int i = 0; i < N / 2; i++)
        for (int j = 0; j < N; j++)
            std::swap(m[i][j], m[N - 1 - i][N - 1 - j]);
    if (N % 2)
        std::reverse(&m[N / 2][0], &m[N / 2][N]);
}

std::vector<double> gauss(std::vector<std::vector<double>> mp, std::vector<double> vp, int N)
{
    std::vector<double> x = std::vector<double>(N, 0);
    std::vector<std::vector<double>> m = std::vector<std::vector<double>>(N);
    for (int i = 0; i < N; i++)
        m[i] = std::vector<double>(N, 0);
    std::vector<double> v = std::vector<double>(N, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            m[i][j] = mp[i][j];
        v[i] = vp[i];
    }
    for (int pass = 0; pass < 2; pass++)
    {
        for (int k = 0; k < N - 1; k++)
            for (int j = k + 1; j < N; j++)
            {
                double c = -m[k][k] / m[j][k];
                for (int i = k; i < N; i++)
                    m[j][i] = c * m[j][i] + m[k][i];
                v[j] = c * v[j] + v[k];
            }
        rotate(m, N);
    std::reverse(&v[0], &v[N]);
    }
    for (int i = 0; i < N; i++)
        x[i] = v[i] / m[i][i];
    return x;
}

bool iter_escape(std::vector<double> x1, std::vector<double> x2, double e, int N)
{
    for (int i = 0; i < N; i++)
        if (fabs(x1[i] - x2[i]) > e)
            return false;
    return true;
}

int zeidel(std::vector<std::vector<double>> m, std::vector<double> v, std::vector<double> x, const double e, int N)
{
    int iter = 0;
    double sum;
    std::vector<double> xp = std::vector<double>(N, 0);
    for (int i = 0; i < N; x[i++] = 0);
    do
        for (int i = 0; i < N; i++)
        {
            for (int j = sum = 0; j < N; j++)
                if (i != j)
                    sum += m[i][j] * x[j];
            xp[i] = x[i];
            x[i] = (v[i] - sum) / m[i][i];
        }
    while (iter++, !iter_escape(x, xp, e, N));
    return iter;
}

int jacobi(std::vector<std::vector<double>> m, std::vector<double> v, std::vector<double> x, const double e, int N)
{
    int iter = 0;
    std::vector<double> xp = std::vector<double>(N, 0);
    for (int i = 0; i < N; x[i++] = 0);
    do
    {
        for (int i = 0; i < N; i++)
            xp[i] = x[i];
        for (int i = 0; i < N; i++)
        {
            for (int j = x[i] = 0; j < N; j++)
                if (i != j)
                    x[i] += m[i][j] * xp[j];
            x[i] = (v[i] - x[i]) / m[i][i];
        }
    } while (iter++, !iter_escape(x, xp, e, N));
    return iter;
}
