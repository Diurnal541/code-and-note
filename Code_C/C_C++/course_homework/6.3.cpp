#include <iostream>
using namespace std;
int oddfactsum(int n);
int fact(int n);
int main()
{
    int n;
    cout << "请输入n:";
    cin >> n;
    int sn = oddfactsum(n);
    cout << "前n项的阶乘和为:" << sn;
    return 0;
}

int oddfactsum(int n)
{
    int sn;
    for (int i = 1; i <= n;i++)
    {
        sn += fact(i);
    }
    return sn;
}

int fact(int n)
{
    int an = 1;
    for (int i = 1; i <= n;i++)
    {
        an *= i;
    }
    return an;
}
