#include <iostream>
#include <iomanip>
using namespace std;
double f(int val)
{
    if (val == 1){
        return 1;
    }
    else {
        return f(val - 1) / val;
    }
}
int main()
{
    int n = 0;
    cin >> n;
    double sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += f(i);
    }
    cout << fixed << setprecision(5) << "sum=" << sum;
    return 0;
}
