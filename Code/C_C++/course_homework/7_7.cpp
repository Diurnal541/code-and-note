// ���ʵ�֣���30��С��Χ��һȦ���ӵ�һ��С����˳ʱ�뷽������ÿ������4��С��ʱ����С�����뿪��С�������뿪��Ȧ�Ӳ�����С�����ʣ�µ�һ��С������ʤ���ߡ�ʤ�����ǵڼ���С���أ�
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
    cout << "����ʤ��С����:" << s << endl;
    return 0;
}
