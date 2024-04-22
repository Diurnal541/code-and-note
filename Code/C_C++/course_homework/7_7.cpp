// 编程实现：有30个小孩围成一圈，从第一个小孩起，顺时针方向数，每数到第4个小孩时，该小孩便离开。小孩不断离开，圈子不断缩小。最后，剩下的一个小孩便是胜利者。胜利者是第几个小孩呢？
#include <iostream>
using namespace std;
int vis[100];
int main()
{
    int s;
    for (int i = 0; i < 30;i++)
    {
        for (int j = 0; j < 4;j++)
        {
            s++;
            if (s > 30)
            {
                s = 1;
            }
            if (vis[s])
            {
                j--;
            }
        }
        vis[s] = 1;
    }
    cout << "最后获胜的小孩是:" << s << endl;
    return 0;
}
