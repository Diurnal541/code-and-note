#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string str;
    getline(cin, str);
    int len = str.length();
    for (int i = 0; i < len;i++)
    {
        if (isalpha(str[i]))
        {
            str[i] = str[i] + 1;
            if (str[i] == 123)
            {
                str[i] = 97;
            }
            cout << str[i] << " ";
        }
    }
    return 0;
}