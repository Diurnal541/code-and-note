#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string str1, str2;
    getline(cin, str1);
    int len = str1.length();
    for (int i = 0; i < len;i++)
    {
        str2[i] = str1[str1.length() - i - 1];
    }
    for (int i = 0; i < len;i++)
    {
        cout << str2[i];
    }
    return 0;
}