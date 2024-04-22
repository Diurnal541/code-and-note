#include <iostream>
using namespace std;
/*
int find_min(int a[], int len)
{
    int min_index = 0;
    for (int i = 0; i < len;i++)
    {
        if (a[i] < a[min_index])
        {
            min_index = i;
        }
    }
    return min_index;
}
*/
int find_min(int *a, int len)
{
    int min_index = 0;
    for (int i = 0; i < len;i++)
    {
        if (*(a + i) < *(a + min_index))
        {
            min_index = i;
        }
    }
    return min_index;
}
int main()
{
    int a[10] = {34, 91, 83, 56, 29, 93, 56, 12, 88, 72};
    int len = sizeof(a) / sizeof(a[0]);
    int min_index = find_min(a, len);
    cout << "最小的数的下标为：" << min_index << endl;
    return 0;
}
