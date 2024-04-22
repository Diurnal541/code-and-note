#include <iostream>
#include <iomanip>
using namespace std;
double fact(int n)
{
    double sum = 1.0;
    for (int i = 1; i <= n; i++)
    {
        sum = sum * i;
    }
    return sum;
}
double mypow(double x, int n)
{
    double sum = 1.0;
    for (int i = 0; i < n; i++)
    {
        sum = sum * x;
    }
    return sum;
}
int main()
{
    double x;
    int n;
    double sum1 = 0;
    double sum2 = 0;
    cin >> x >> n;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            sum1 = sum1 + (-1.0 * mypow(x, i) / fact(i));
        }
        else if (i % 2 == 1)
        {
            sum2 = sum2 + mypow(x, i) / fact(i);
        }
    }
    cout << fixed << setprecision(4) << sum1 + sum2 << endl;
    return 0;
}
