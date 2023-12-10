#include <bits/stdc++.h>
using namespace std;
struct peo
{
    int ID; 
    peo *next = NULL, *front = NULL;
} n[100];
void cut(peo *num)
{
    num = num->front;
    num->next = num->next->next;
    num = num->next;
    num->front = num->front->front;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tot, nowNum = 1;
    peo *now = &n[0]; 
    cin >> tot;       
    for (int i = 1; i < tot - 1; i++)
    {
        n[i].front = &n[i - 1];
        n[i].next = &n[i + 1];
        n[i].ID = i + 1;
    }
    n[0].front = &n[tot - 1];
    n[0].next = &n[1];
    n[tot - 1].front = &n[tot - 2];
    n[tot - 1].next = &n[0];
    n[0].ID = 1;
    n[tot - 1].ID = tot; //22行到33行为初始化链表
    while (tot > 0)
    {
        if (nowNum == 3)
        {
            if (tot == 1)
            {
                cout << now->ID; 
            }
            cut(now);
            nowNum = 1; 
            tot--;
            now = now->next; 
        }
        else
        {
            nowNum++;        
            now = now->next; 
        }
    }
    return 0;
}
