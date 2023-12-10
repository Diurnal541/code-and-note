#include <bits/stdc++.h> //约瑟夫环问题 有n人围成一圈，顺序排号。从第1个人开始报数（从1到3报数），凡报到3的人退出圈子，问最后留下的是原来的第几号的那位。
using namespace std;
int vis[100];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, s;
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        for (int k = 0; k < 3;k++)
        {
            s++;
            if (s > n)
            {
                s = 1;
            }
            if (vis[s])
            {
                k--;
            }
        }
        vis[s] = 1;
    }
    cout << s;
    return 0;
}
