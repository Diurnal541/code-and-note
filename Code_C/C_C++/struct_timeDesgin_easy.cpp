#include <bits/stdc++.h>
using namespace std;
struct date
{
    int year;
    int month;
    int day;
};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int m = 1, d = 1, zd = 1, arr[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    date time;
    cin >> time.year >> time.month >> time.day;
    if ((time.year % 4 == 0 && time.year % 100 != 0) || time.year % 400 == 0)
    {
        arr[2] = 29;
    }
    while (!(m == time.month && d == time.day))
    {
        d++;
        zd++;
        if (d > arr[m])
        {
            d = 1;
            m++;
        }
    }
    cout << zd;
    return 0;
}