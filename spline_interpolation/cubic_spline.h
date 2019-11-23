#pragma once
#include <vector>
#include <utility>
using namespace std;

class point_cl
{
public:
    int x, y;
    point_cl() {}
    ~point_cl() {}
    point_cl(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

void CubicSplie(vector<pair<int, int>> _vector, double** answer, int n);

void Sweep(int** left, double* right, double* result, int n);
