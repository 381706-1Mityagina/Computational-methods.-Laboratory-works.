#include <stdio.h>
#include <stdlib>
#include <iostream>

namespace SLAE
{
    class LUDecomposition : SLAEMethod
    {
        private void LUDecompose(ref double[,] matrix, out double[,] L, out double[,] U)
        {
            int length = matrix.GetLength(0);
            L = new double[length, length];
            U = new double[length, length];

            for (int j = 0; j < length; j++)
            {
                U[0, j] = matrix[0, j];
                L[j, 0] = matrix[j, 0] / U[0, 0];
            }

            for (int i = 1; i < length; i++)
            {
                for (int j = i; j < length; j++)
                {
                    double sum = 0.0;
                    for (int k = 0; k < i; k++)
                    {
                        sum += L[i, k] * U[k, j];
                    }

                    U[i, j] = matrix[i, j] - sum;
                }

                for (int j = i; j < length; j++)
                {
                    double sum = 0.0;
                    for (int k = 0; k < i; k++)
                    {
                        sum += L[j, k] * U[k, i];
                    }

                    L[j, i] = (matrix[j, i] - sum) / U[i, i];
                }
            }
        }

        public override double[] Solve(double[,] matrix, double[] b)
        {
            int length = matrix.GetLength(0);

            LUDecompose(ref matrix, out double[,] L, out double[,] U);

            double[] y = new double[length];
            for (int i = 0; i < length; i++)
            {
                double sum = 0.0;
                for (int j = 0; j < i; j++)
                {
                    sum += L[i, j] * y[j];
                }

                y[i] = b[i] - sum;
            }

            double[] x = new double[length];
            for (int i = length - 1; i >= 0; i--)
            {
                double sum = 0.0;
                for (int j = i + 1; j < length; j++)
                {
                    sum += U[i, j] * x[j];
                }

                x[i] = (y[i] - sum) / U[i, i];
            }

            return x;
        }
    }
}
