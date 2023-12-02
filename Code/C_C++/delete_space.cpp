#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    string str;
    while (getline(cin,str))
    {
        int len = str.length();
        for (int i = 0; i < len;i++)
        {
            if (str[i] != 32)
            {
                cout << str[i];
            }
        }
        cout << endl;
    }
    return 0;
}