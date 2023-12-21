#include <stdio.h>
int int_sum(int m, int n);   // 求m~n的和并返回
int Is_square(int m, int n); // 判断区间[m,n]表示是否正确
int main()
{
    int m, n, s;
    scanf("%d", &m);
    scanf("%d", &n);
    if (Is_square(m, n))
    {
        s = int_sum(m, n); /*【1】*/
        printf("区间[%d,%d]累加和为:%d", m, n, s);
    }
    else
    {
        s = int_sum(n, m);
        printf("区间[%d,%d]累加和为:%d", n, m, s);
    }
    return 0;
}
int int_sum(int m, int n)
{
    int s = 0;          /*【2】*/
    for (; m <= n; m++) /*【3】*/
        s = s + m;
    return s;
}
int Is_square(int m, int n)
{
    return m > n ? 0 : 1;
}
