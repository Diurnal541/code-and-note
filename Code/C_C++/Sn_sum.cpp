// 求Sn=a+aa+aaa+…+aa…aaa（有n个a）之值，其中a是一个数字，为2。 例如，n=5时=2+22+222+2222+22222，n由键盘输入。
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, arr[100], sum = 0;
    cin >> n;
    arr[0] = 2;
    for (int i = 0; i < n - 1;i++)
    {
        arr[i + 1] = arr[i] * 10 + 2;
    }
    for (int i = 0; i < n;i++)
    {
        sum += arr[i];
    }
    cout << sum;
    return 0;
}
