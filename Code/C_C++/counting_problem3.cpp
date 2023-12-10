#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tot, nowNum;
    queue<int> q;//stl
    cin >> tot;
    for (int i = 1; i <= tot;i++)
    {
        q.push(i);//³õÊ¼»¯
    }
    while (!q.empty())
    {
        if (nowNum == 3)
        {
            if (q.size() == 1)
            {
                cout << q.front() << " ";
            }
            q.pop();
            nowNum = 1;
        }
        else
        {
            nowNum++;
            q.push(q.front());
            q.pop();
        }
    }
    return 0;
}
