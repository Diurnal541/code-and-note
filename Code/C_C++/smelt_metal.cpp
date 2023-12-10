#include <iostream>
using namespace std;
int main()
{
    int n, a, b, max, min, flag = 0;
    cin >> n;
    while (n--)
    {
        cin >> a >> b;
        if (a / b < max && flag == 1)
        {
            max = a / b;
        }
        if (a / (b + 1) > min && flag == 1)
        {
            min = a / (b + 1);
        }
        if (flag == 0)
        {
            max = a / b;
            min = a / (b + 1);
            flag = 1;
        }
    }
    cout <<  min + 1 << " " << max;
    return 0;
}
