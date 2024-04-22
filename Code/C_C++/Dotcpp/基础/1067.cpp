#include <iostream>
#include <cmath> //平方根函数,绝对值函数和幂函数的头文件
using namespace std;
int main()
{
    double x, ans = 0; // 因为要保留两位小数所以用double
    cin >> x;
    if (x < 0)
    {
        ans = abs(x);
    }
    if (x >= 0 && x < 2)
    {
        ans = sqrt(x + 1);
    }
    if (x >= 2 && x < 4)
    {
        ans = pow(x + 2, 5);
    }
    if (x > 4)
    {
        ans = 2 * x + 5;
    }
    printf("%.2f", ans); // 不要忘记题目中说的两位小数
    return 0;
}
