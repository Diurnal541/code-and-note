#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, s = 0;
    cin >> n;
    for (int i = 2; i <= n;i++)
    {
        s = (s + 3) % i;
    }
    cout << s + 1;
    return 0;
}
//看不懂一点!!!!!!!
