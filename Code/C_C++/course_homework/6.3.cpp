#include <iostream>
using namespace std;
int oddfactsum(int n);
int fact(int n);
int main()
{
    int n;
    cout << "������n:";
    cin >> n;
    int sn = oddfactsum(n);
    cout << "ǰn��Ľ׳˺�Ϊ:" << sn;
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
