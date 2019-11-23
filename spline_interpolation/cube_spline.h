#pragma once
double* Smoothing_Spine(double* X, double* F_wrong, double* P, const int& N);
double Cubic_Spline(double x, double* X, double* F, double* M, const int& N);
double* Cubic_Spline_Vector(double** X, double** F, const int& N);
double* GaussMethod(double** A,double* b, const int& m);
double* TridiagonalSolve(const double *a, const double *b, double *c, double *d, const int& n);
double* TridiagonalSolve(const int *a, const int *b, double *c, int *d, const int& n);
