#include <iostream>
using namespace std;
/*
������n       1            2          3             4           ����������          n
����ֵan      1            3          5             7           ����������        2n-1
�۳˻�sn      1            3          15            105         ����������       sn = (2n - 1) * sn-1
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
    cout << "������һ������:";
    cin >> n;
    int sn = sum(n);
    cout << "�۳˻�Ϊ:" << sn << endl;
    return 0;
}
