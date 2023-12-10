#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string str;
    getline(cin, str);
    int len = str.length();
    int count = 0;
    for (int i = 0; i < len;i++)
    {
        if (isalpha(str[i]))
        {
            count++;
        }
    }
    cout << count;
    return 0;
}