// ��Sn=a+aa+aaa+��+aa��aaa����n��a��ֵ֮������a��һ�����֣�Ϊ2�� ���磬n=5ʱ=2+22+222+2222+22222��n�ɼ������롣
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
