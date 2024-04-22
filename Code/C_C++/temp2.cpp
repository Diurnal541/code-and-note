#include <iostream>
#include <cstring>
using namespace std;
const int N = 10010;
int a[N], n;
void dfs(int t, int x)
{
    if (t > n)
        return;
    if (t == n)
    {
        cout << n << '=' << a[0];
        for (int i = 1; i < x; i++)
            cout << '+' << a[i];
        cout << endl;
        return;
    }
    if (t < n)
    {
        for (int i = 1; i <= n - t && i < n; i++) // 保证字典序
        {
            if (x == 0) // 第一个数 从i开始 没有限制
            {
                a[x] = i;
                dfs(t + i, x + 1);
            }
            else
            {
                if (i >= a[x - 1]) // 保证字典序 后一个数必须大于等于前一个数
                {
                    a[x] = i;
                    dfs(t + i, x + 1);
                }
            }
        }
    }
}

int main(void)
{
    a[0] = 0;
    cin >> n;
    dfs(0, 0); // 加和 和 个数
    return 0;
}