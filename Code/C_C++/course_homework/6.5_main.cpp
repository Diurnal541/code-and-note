#include "6.5.h"
int main()
{
    int n;
    cout << "ÇëÊäÈën:";
    cin >> n;
    int a1 = sum1(n);
    int a2 = sum2(n);
    int a3 = sum3(n);
    int a4 = sum4(n);
    cout << a1 << endl
         << a2 << endl
         << a3 << endl
         << a4 << endl;
    return 0;
}