#include <stdio.h>
int int_sum(int m, int n);   // ��m~n�ĺͲ�����
int Is_square(int m, int n); // �ж�����[m,n]��ʾ�Ƿ���ȷ
int main()
{
    int m, n, s;
    scanf("%d", &m);
    scanf("%d", &n);
    if (Is_square(m, n))
    {
        s = int_sum(m, n); /*��1��*/
        printf("����[%d,%d]�ۼӺ�Ϊ:%d", m, n, s);
    }
    else
    {
        s = int_sum(n, m);
        printf("����[%d,%d]�ۼӺ�Ϊ:%d", n, m, s);
    }
    return 0;
}
int int_sum(int m, int n)
{
    int s = 0;          /*��2��*/
    for (; m <= n; m++) /*��3��*/
        s = s + m;
    return s;
}
int Is_square(int m, int n)
{
    return m > n ? 0 : 1;
}
