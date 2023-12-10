#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int a = 0, b = 0, c = 0, d = 0;
    string str;
    getline(cin, str);
    for (int i = 0; str[i] != '\0';i++)
    {
        if (isalpha(str[i]))
        {
            a++;
        }
        else if (isdigit(str[i]))
        {
            b++;
        }
        else if (isspace(str[i]))
        {
            c++;
        }
        else
        {
            d++;
        }
    }
    cout << a << " " << b << " " << c << " " << d;
    return 0;
}
