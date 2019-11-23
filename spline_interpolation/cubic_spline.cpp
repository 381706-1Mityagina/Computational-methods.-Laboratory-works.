#include "cubic_spline.h"

void CubicSplie(vector<pair<int, int>> _vector, double** answer, int n)
{
  int* h = new int[n];
  h[0] = 0;
  for (int i = 1; i < n; ++i)
      h[i] = _vector[i].first - _vector[i - 1].first;

  double* right = new double[n - 2];
  int** left = new int*[n - 2];

  for (int i = 0; i < n - 2; ++i)
  {
    left[i] = new int[n];
    for (int j = 0; j < n; ++j)
        left[i][j] = 0;
  }

  for (int i = 1; i < n - 1; ++i)
  {
    double one = ((double)_vector[i + 1].second - (double)_vector[i].second) / (double)h[i + 1];
    double two = ((double)_vector[i].second - (double)_vector[i - 1].second) / (double)h[i];
    right[i - 1] = 3. * (one - two);

    left[i - 1][i - 1] = h[i];
    left[i - 1][i] = 2 * (h[i + 1] + h[i]);
    left[i - 1][i + 1] = h[i + 1];
  }

  double* solutn = new double[n - 2];
  Sweep(left, right, solutn, n);

  double* C = new double[n + 1];
  C[1] = C[n] = 0;
  for (int i = 2; i < n; ++i)
      C[i] = solutn[i - 2];

  for (int i = 1; i < n; ++i)
  {
    double one = ((double)(_vector[i].second - _vector[i - 1].second) / (double)h[i]);
    double two = (C[i] * h[i]) + ((double)(C[i + 1] - C[i]) / 3.) * h[i];
    answer[i][0] = _vector[i - 1].second;
    answer[i][1] = one - two;
    answer[i][2] = C[i];
    answer[i][3] = (C[i + 1] - C[i]) / (3. * h[i]);
  }

  for (int i = 0; i < n - 2; ++i)
      delete[] left[i];
  delete[] right;
  delete[] left;
  delete[] h;
  delete[] solutn;
  delete[] C;
}

void Sweep(int** left, double* B, double* result, int n)
{
  int size = n - 2;
  double* a = new double[size];
  double* b = new double[size];

  double** A = new double*[size];
  for (int i = 0; i < size; ++i)
  {
    A[i] = new double[size];
    for (int j = 0; j < size; ++j) A[i][j] = left[i][j + 1];
  }

  double y = (double)A[0][0];
  a[0] = -1. * (double)A[0][1] / y;
  b[0] = B[0] / y;
  for (int i = 1; i < size - 1; ++i)
  {
    y = A[i][i] + A[i][i - 1] * a[i - 1];
    a[i] = -1 * A[i][i + 1] / y;
    b[i] = (B[i] - A[i][i - 1] * b[i - 1]) / y;
  }

  double one = (B[size - 1] - A[size - 1][size - 2] * b[size - 2]);
  double two = (A[size - 1][size - 1] + A[size - 1][size - 2] * a[size - 2]);
  result[n - 3] = one / two;
  for (int i = size - 2; i >= 0; i--)
      result[i] = a[i] * result[i + 1] + b[i];

  for (int i = 0; i < size; ++i)
      delete[] A[i];
  delete[] a;
  delete[] b;
  delete[] A;
}