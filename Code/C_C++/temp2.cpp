#include <iostream>
using namespace std;
double Sum(int n)
{
    if (n == 1)
    {
        return 2;
    }
    else
    {
        return 2 * n * Sum(n - 1);
    }
}
int main()
{
    int n;
    cin >> n;
    cout << Sum(n) << endl;
    return 0;
}
