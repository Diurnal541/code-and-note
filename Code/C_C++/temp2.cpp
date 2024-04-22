#include <iostream>
#include <cstring>
using namespace std;
const int N = 10010;
int a[N], n;
void dfs(int t, int x)
{
    if (t > n)
        return;
    if (t == n)
    {
        cout << n << '=' << a[0];
        for (int i = 1; i < x; i++)
            cout << '+' << a[i];
        cout << endl;
        return;
    }
    if (t < n)
    {
        for (int i = 1; i <= n - t && i < n; i++) // ��֤�ֵ���
        {
            if (x == 0) // ��һ���� ��i��ʼ û������
            {
                a[x] = i;
                dfs(t + i, x + 1);
            }
            else
            {
                if (i >= a[x - 1]) // ��֤�ֵ��� ��һ����������ڵ���ǰһ����
                {
                    a[x] = i;
                    dfs(t + i, x + 1);
                }
            }
        }
    }
}

int main(void)
{
    a[0] = 0;
    cin >> n;
    dfs(0, 0); // �Ӻ� �� ����
    return 0;
}