// һ�������ǡ�õ��ڲ�������������������֮�ͣ�������ͳ�Ϊ"����"�� ���磬6������Ϊ1��2��3����6=1+2+3�����6��"����"�� ������ҳ�N֮�ڵ���������
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, arr[1001];
    cin >> n;
    for (int i = 1; i <= n;i++)
    {
        int temp = 0, k = 0;
        for (int j = 1; j < i;j++)
        {
            if (i % j == 0)
            {
                temp += j;
                arr[k++] = j;
            }
        }
        if (temp == i)
        {
            cout << i << " " << "its factors are";
            for (int l = 0; l < k;l++)
            {
                cout << " " << arr[l];
            }
            cout << endl;
        }
    }
    return 0;
}
