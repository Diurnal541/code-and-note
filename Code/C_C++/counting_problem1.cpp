#include <bits/stdc++.h> //Լɪ������ ��n��Χ��һȦ��˳���źš��ӵ�1���˿�ʼ��������1��3��������������3�����˳�Ȧ�ӣ���������µ���ԭ���ĵڼ��ŵ���λ��
using namespace std;
int vis[100];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, s;
    cin >> n;
    for (int i = 0; i < n;i++)
    {
        for (int k = 0; k < 3;k++)
        {
            s++;
            if (s > n)
            {
                s = 1;
            }
            if (vis[s])
            {
                k--;
            }
        }
        vis[s] = 1;
    }
    cout << s;
    return 0;
}
