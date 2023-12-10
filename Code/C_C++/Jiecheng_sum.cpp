//求Sn = 1 !+2 !+3 !+4 !+5 !+…+ n !之值，其中n是一个数字(n不超过20)。
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, sn = 0;
    cin >> n;
    int arr[n];
    arr[0] = 1;
    for (int i = 1; i <= n;i++)
    {
        arr[i] = arr[i - 1] * i;
    }
    for (int i = 1; i <= n;i++)
    {
        sn += arr[i];
    }
    cout << sn;
    return 0;
}
