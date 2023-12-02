#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5;
int N, dp[10];
string A[MAX_N];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for (int i = 0; i <= N;i++)
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
        dp[y] = max(dp[y], dp[x] + 1);
    }
    int len = 0;
    for (int i = 0; i < 10;i++)
    {
        len = max(len, dp[i]);
    }
    cout << N - len;
    return 0;
}