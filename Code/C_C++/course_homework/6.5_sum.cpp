#include "6.5.h"

int sum1(int n)
{
    int an = 1;
    for (int i = 1; i <= n;i++)
    {
        an *= i;
    }
    return an;
}

int sum2(int n)
{
    int an = 1;
    while (n > 0)
    {
        an *= n;
        n--;
    }
    return an;
}

int sum3(int n)
{
    int an = 1;
    do
    {
        an *= n;
        n--;
    } while (n > 0);
    return an;
}

int sum4(int n)
{
    if (n == 1)
    {
        return 1;
    }
    return n * sum4(n - 1);
}
