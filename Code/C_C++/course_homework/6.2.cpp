#include <iostream>
using namespace std;
/*
数列项n       1            2          3             4           。。。。。          n
数列值an      1            3          5             7           。。。。。        2n-1
累乘积sn      1            3          15            105         。。。。。       sn = (2n - 1) * sn-1
*/
int sum(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return (2 * n - 1) * sum(n - 1);
}
int main()
{
    int n;
    cout << "请输入一个数字:";
    cin >> n;
    int sn = sum(n);
    cout << "累乘积为:" << sn << endl;
    return 0;
}
