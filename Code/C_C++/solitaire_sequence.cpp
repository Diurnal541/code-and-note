#include <bits/stdc++.h>
using namespace std;
int N, dp[10];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i < N;i++)
    {
        int A;
        cin >> A;
        vector<int> d;
        while (A)
        {
            d.push_back(A % 10);
            A /= 10;
        }
        int y = *d.begin(), x = d.back();
        dp[y] = max(dp[y], dp[x] + 1);     // 以数字 y 结尾的最长非递减子序列的长度，等于以数字 x 结尾的最长非递减子序列的长度加1,
    }                                      // 也就是说，如果我们找到了一个以数字 x 结尾的更长的非递减子序列，那么可以将数字 y 加在后面形成一个更长的非递减子序列。
    int len = 0;
    for (int i = 0; i < 10;i++)
    {
        len = max(len, dp[i]);
    }
    cout << N - len;
    return 0;
}
