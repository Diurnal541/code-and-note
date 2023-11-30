#include <iostream>
using namespace std;
void selectsort(int arr[], int len)
{
    int start = 0, end = len - 1;
    while (start < end)
    {
        int max = start;
        int min = start;
        int j;
        for (j = start; j <= end; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
            if (arr[j] > arr[max])
            {
                max = j;
            }
        }
        int temp = arr[min];
        arr[min] = arr[start];
        arr[start] = temp;
        if (start == max)
        {
            max = min;
        }
        temp = arr[max];
        arr[max] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main()
{
    int arr[10] = {2, 3, 15, 64, 7, 8, 9, 23, 4, 5};
    int len = sizeof(arr) / sizeof(arr[0]);
    selectsort(arr, len);
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}