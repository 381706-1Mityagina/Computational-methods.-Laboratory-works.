#include <iostream>
#include <vector>
#include <iomanip>
#include <math.h>

namespace SLAE
{
    std::vector<double> Solve_Yakobi(std::vector<std::vector<double>> matrix, std::vector<double> vector, int n, double epsilon)
    {
        std::vector<double> NextX = std::vector<double>(n, 0);
        std::vector<double> x = std::vector<double>(n, 0);
        int k = 0;
        double norm = 0;
        do {
            for (int i = 0; i < n; ++i) {
                double sum = 0;
                for (int j = 0; j < n; ++j) {
                    if (i != j) {
                        sum = sum + matrix[i][j] * x[j];
                    }
                }
                NextX[i] = (vector[i] - sum) / matrix[i][i];
            }

            norm = fabs(NextX[1] - x[1]);
            for (int i = 0; i < n; ++i) {
                if (fabs(NextX[i] - x[i]) > norm) {
                    norm = fabs(NextX[i] - x[i]);
                }
                x[i] = NextX[i];
            }
            k++;
        } while (norm > epsilon);

        return x;
    }
}
