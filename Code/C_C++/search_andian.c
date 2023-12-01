#include <stdio.h>
int main()
{
    int arr[100][100];
    int n, max, min;
    scanf("%d", &n);
    for (int i = 0; i < n;i++)
    {
        for (int j = 0; j < n;j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    for (int i = 0; i < n;i++)
    {
        max = arr[i][0];
        int index = 0;
        for (int j = 0; j < n;j++)
        {
            if (arr[i][j] > max)
            {
                max = arr[i][j];
                index = j;
            }
        }
        min = arr[0][index];
        for (int k = 0; k < n;k++)
        {
            if (arr[k][index] < min)
            {
                min = arr[k][index];
            }
        }
        if (max == min)
        {
            printf("%d", max);
            return 0;
        }
    }
    printf("NO");
    return 0;
}
