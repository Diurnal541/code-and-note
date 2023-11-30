#include <iostream>
using namespace std;
int a[100], ans;
bool vis[20240000];
bool check(int date)
{
    if (vis[date])
    {
        return false;
    }
    vis[date] = 1;
    int mm = date / 100 % 100;
    int dd = date % 100;
    if (mm < 1 || 12 < mm)
    {
        return false;
    }
    if (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12 )
    {
        if (1 <= dd && dd <= 31)
        {
            return true;
        }
    }
    else if (mm == 2)
    {
        if (1 <= dd && dd <= 28)
        {
            return true;
        }
    }
    else if (1 <= dd && dd <= 30)
    {
        return true;
    }
    else 
    {
        return false;
    }
    return false;
}

void dfs(int x,int pos,int date)
{
    if (x == 100)
    {
        return;
    }
    if (pos == 8)
    {
        if (check(date))
        {
            ++ans;
        }
        return;
    }
    if ((pos == 0 && a[x] == 2) ||
        (pos == 1 && a[x] == 0) ||
        (pos == 2 && a[x] == 2) ||
        (pos == 3 && a[x] == 3) ||
        (pos == 4 && 0 <= a[x] && a[x] <= 1) ||
        (pos == 5 && 0 <= a[x] && a[x] <= 9) ||
        (pos == 6 && 0 <= a[x] && a[x] <= 3) ||
        (pos == 7 && 0 <= a[x] && a[x] <= 9))
        {
            dfs(x + 1, pos + 1, date * 10 + a[x]);
        }
        dfs(x + 1, pos, date);
}


int main()
{
    for (int i = 0; i < 100;i++)
    {
        cin >> a[i];
    }
    dfs(0, 0, 0);
    cout << ans << endl;
    system("pause");
    return 0;
}
    