#ifndef RK_FOR_LORENZ_H
#define RK_FOR_LORENZ_H

#include <iostream>
#include <math.h>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <string>
#include <QGraphicsPixmapItem>

using namespace std;

long double *rungekutta(long double t0, long double u0[], long double h);
long double *lorenz(long double x[]);

int main_work() {
    //Open files to write output
    ofstream fil("Data.dat");
    long double t0 = 0.0; // отрезок времени (t[start])?
    long double tf = 30.0; // отрезок времени (t[last])?
    int n = 2000;
    long double dt;
    long double *values = new long double[n];
    long double *val;
    long double D[3] = { 17.0, 13.0, 7.0 };
    long double xpos1[1000]; // 1000 - size (отрезок интегрирования?)
    long double xpos2[1000];
    double step = 2.0;
    dt = (tf - t0) / (long double)(n); // step?
    int j = 0;
    val = rungekutta(t0, D, dt); // dt - step?
                                 // D  - coeff-s?
                                 // t0 - moment t[i]?
    fil << val[0] << "     " << val[1] << "     " << val[2] << "\n";

    //For n points run RK4 to solve Lorenz equations
    for (int i = 0; i < n; i+=step) {
        val = rungekutta(t0, val, dt);
        fil << val[0] << "     " << val[1] << "     " << val[2] << "\n";
        if (i < 1000) {
            xpos1[i] = val[0];
        }
        if (i > 8 && j<1000) {
            xpos2[j] = val[0];
            j++;
        }
    }
    //Closing filestreams
    fil.close();
    delete[] val;
    return 0;
}

//Lorenz Attractor
long double *lorenz(long double x[]) {
    long double B = 8.0 / 3.0;
    long double R = 28.0;
    long double sigma = 10.0;

    long double *dxdt = new long double[3];

    dxdt[0] = sigma * (x[1] - x[0]);
    dxdt[1] = x[0] * (R - x[2]) - x[1];
    dxdt[2] = x[0] * x[1] - B * x[2];

    return dxdt;
}

//RK4
long double *rungekutta(long double t0, long double u0[], long double h){
    long double t1, t2, t3;
    vector<long double> f1(3), f2(3), f3(3), f4(3);
    vector<long double> u(3), u1(3), u2(3), u3(3);

    f1 = lorenz(u0);
    t1 = t0 + h / 2;
    for (int i = 0; i < 3; i++)
        u1[i] = u0[i] + h*f1[i] / 2.0;

    f2 = lorenz(u1);
    t2 = t0 + h / 2;
    for (int i = 0; i < 3; i++)
        u2[i] = u0[i] + h * f2[i] / 2.0;

    f3 = lorenz(u2);
    t3 = t0 + h;
    for (int i = 0; i < 3; i++)
        u3[i] = u0[i] + h * f3[i];

    f4 = lorenz(u3);
    for (int i = 0; i < 3; i++)
        u[i] = u0[i] + h * (f1[i] + 2.0 * f2[i] + 2.0 * f3[i] + f4[i]) / 6.0;
    return u;
}

#endif // RK_FOR_LORENZ_H
