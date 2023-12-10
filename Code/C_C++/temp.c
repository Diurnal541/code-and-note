#include <stdio.h>
int main()
{
    int c, d;
    scanf("%d%d", &c, &d);
    int a = c;
    int b = d;
    int e;
    if (a % b == 0)
    {
        if (a > b)
        {
            printf("%d\n", b);
        }
        else
        {
            printf("%d\n", a);
        }
    }
    else
    {
        while (a % b) // a%b!=0
        {
            e = a % b;
            a = b;
            b = e;
        }
        printf("%d ", e);
    }
    if (c / d >= 2)
        printf("%d", c);
    else if (d / c >= 2)
        printf("%d", d);
    else
        printf("%d", c * d);
    return 0;
}
