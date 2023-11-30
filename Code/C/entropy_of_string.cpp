#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    int n = 23333333;
    double a = 11625907.5798, eps = 1e-4;
    int u, v;
    long double c;
    for (u = 1; u <= n / 2; u++)
    {
        v = n - u;
        c = -1.0 * u * u / n * log2(1.0 * u / n) - 1.0 * v * v / n * log2(1.0 * v / n);
        if (fabs(c - a) <= eps)
        {
            cout << u;
            return 0;
        }
    }
    return 0;
}

/*
´ð°¸£º11027421
*/