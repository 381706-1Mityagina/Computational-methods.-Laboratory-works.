#include <iostream>
#include <math.h>
#include <iomanip>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

long double *rungekutta(long double t0, long double u0[], long double h);
long double *lorenz(long double x[]);

int main() {
	//Open files to write output
	ofstream fil("Data.dat");
	long double t0 = 0.0; // отрезок времени (t[start])?
	long double tf = 30.0; // отрезок времени (t[last])?
	int n = 2000; // number of steps
	long double dt;
	long double *values = new long double[n];
	long double *val;
	long double D[3] = { 17.0, 13.0, 7.0 };
	int step = 2;
	long double xpos1[n / step]; // 1000 - size (отрезок интегрирования?)
	long double xpos2[n / step];

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
	long double B = 8.0 / 3.0; // slide bar?
	long double R = 28.0;      // slide bar?
	long double sigma = 10.0;  // slide bar?

	long double *dxdt = new long double[3];

	// dxdt = sigma(y - x)
	// dydt = x(r - z) - y
	// dzdt = xy - bz

	// dxdt[0] = x[1];
	// dxdt[1] = -2*x[1] - 5*x[0];
	// dxdt[2] = 0;

	dxdt[0] = sigma * (x[1] - x[0]);
	dxdt[1] = x[0] * (R - x[2]) - x[1];
	dxdt[2] = x[0] * x[1] - B * x[2];
	
	return dxdt;
}

//RK4
long double *rungekutta(long double t0, long double u0[], long double h){
	long double t1, t2, t3;
	long double *f1, *f2, *f3, *f4;
	long double *u, *u1, *u2, *u3;

	f1 = lorenz(u0);
	t1 = t0 + h / 2;
	u1 = new long double[3];
	for (int i = 0; i < 3; i++) { 
		u1[i] = u0[i] + h*f1[i] / 2.0;
	}

	f2 = lorenz(u1);
	t2 = t0 + h / 2;
	u2 = new long double[3];
	for (int i = 0; i < 3; i++) {
		u2[i] = u0[i] + h * f2[i] / 2.0;
	}
	
	f3 = lorenz(u2);
	t3 = t0 + h;
	u3 = new long double[3];
	for (int i = 0; i < 3; i++) {
		u3[i] = u0[i] + h * f3[i];
	}

	f4 = lorenz(u3);
	u = new long double[3];
	for (int i = 0; i < 3; i++) {
		u[i] = u0[i] + h * (f1[i] + 2.0 * f2[i] + 2.0 * f3[i] + f4[i]) / 6.0;
	}
	delete[] f1;
	delete[] f2;
	delete[] f3;
	delete[] f4;
	delete[] u1;
	delete[] u2;
	delete[] u3;
	return u;
}
