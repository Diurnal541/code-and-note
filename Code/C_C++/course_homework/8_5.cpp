#include <iostream>
#include <ctime>
using namespace std;
void bubble(int *arr,int len)
{
    bool flag = true;
    for (int i = 0; i < len - 1;i++)
    {
        if (!flag)
        {
            break;
        }
        flag = false;
        for (int j = 0; j < len - i - 1;j++)
        {
            if (*(arr + j) > *(arr + j + 1))
            {
                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
                flag = true;
            }
        }
    }
}
void print(int *arr,int len)
{
    for (int i = 0; i < len;i++)
    {
        cout << *(arr + i) << " ";
    }
}
int main()
{
    srand(time(0));
    int arr[10];
    int len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < len;i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    bubble(arr, len);
    print(arr, len);
    return 0;
}
