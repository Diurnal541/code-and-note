#include <iostream>
using namespace std;
double *sum()
{
    double *p = new double[20];
    //double *p = (double *)malloc(20 * sizeof(double));
    p[0] = 1.5;
    for (int i = 1; i < 20;i++)
    {
        p[i] = p[i - 1] * 3 + 1.5;
    }
    return p;
}
int main()
{
    double *p = sum();
    for (int i = 0; i < 20;i++)
    {
        cout << p[i] << endl;
    }
    //free(p);
    delete[] p;
    return 0;
}
// ���벻�����ڴ��������ڷ����ڴ�ʱ��û�з����㹻���ڴ棬����������������������С��20
// ������ڴ治�㣬�������ڴ��Ѿ�ȫ���ľ�
// �ڴ�й¶���ѷ�����ڴ�û�б���ȷ�ͷţ����¶��ڴ汻ռ�ã��Ӷ��޷������µ��ڴ�
