#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string str;
    getline(cin, str);
    int len = str.length();
    for (int i = 0; i < len; i++)
    {
        if (isupper(str[i]))
        {
            str[i] = tolower(str[i]);
        }
    }
    for (int i = 0; i < len; i++)
    {
        cout << str[i];
    }
    return 0;
}
