#include <bits/stdc++.h>
using namespace std;
bool judge(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return true;
    }
    return false;
}
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
    int n;
    struct date time1;
    cin >> time1.year >> time1.month >> time1.day;
    if (judge(time1.year))
    {
        for (int i = 1; i < time1.month;i++)
        {
            switch(i)
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    n += 31;
                    break;
                case 2:
                    n += 29;
                    break;
                default:
                    n += 30;
                    break;
            }
        }
        n += time1.day;
    }
    else
    {
        for (int i = 1; i < time1.month;i++)
        {
            switch(i)
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    n += 31;
                    break;
                case 2:
                    n += 28;
                    break;
                default:
                    n += 30;
                    break;
            }
        }
        n += time1.day;
    }
    cout << n;
    return 0;
}
