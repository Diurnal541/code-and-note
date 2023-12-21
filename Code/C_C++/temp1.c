#include <stdio.h>
int Count(int, int);
int main()
{
    int num, digit, count = 0;
    printf("Enter num and digit:");
    scanf("%d %d", &num, &digit);
    count = Count(num, digit);
    printf("%d in %d is %d", digit, num, count);
    return 0;
}
int Count(int num, int digit)
{
    int count;
    if (num == 0 && digit == 0)
    {
        return 1;
    }
    while (num != 0)
    {
        int a = num % 10;
        if (a == digit)
        {
            count++;
        }
        num /= 10;
    }
    return count;
}
    