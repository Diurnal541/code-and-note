#include <iostream>                                               //2
#include <algorithm>                                              //3
using namespace std;                                              //0 100 10
const int MAX_N = 10;                                             //10 10 10
int t[MAX_N], d[MAX_N], l[MAX_N];                                 //0 2 20
int T, N, D, L;                                                   //3
bool have_answer, used[MAX_N];                                    //0 10 20
void dfs(int x,int tim)                                           //10 10 20
{                                                                 //20 10 20
    if (have_answer)                                              //dps(0,0)分i=0,i=1,i=2三种，分别进入dps(1,10),dps(1,20),dps(1,20)
    {                                                             //第一次的i=0,i=1,i=2分别表示从第一个飞机开始降落或从第二个飞机开始降落或第三个飞机开始降落
        return;                                                   //开始深度搜索,将每一种可能遍历一遍，直到找到符合条件的情况，即从第三个飞机开始，第二个其次，
    }                                                             //第二组数据同理,最后发现没有符合的情况
    if (x == N)                                                   
    {                                                             
        have_answer = 1;                                          
        return;                                                   
    }                                                             
    for (int i = 0; i < N;i++)                                    
    {                                                             
        if (!used[i] && tim <= t[i] + d[i])
        {
            used[i] = 1;
            dfs(x + 1, max(t[i], tim) + l[i]);
            if (have_answer)
            {
                return;
            }
            used[i] = 0;
        }
    }
}                                                                  
void solve()
{
    have_answer = 0;
    cin >> N;
    for (int i = 0; i < N;i++)
    {
        cin >> t[i] >> d[i] >> l[i];
        used[i] = 0;
    }
    dfs(0, 0);
    if (have_answer)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}
int main()
{
    have_answer = 0;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}
