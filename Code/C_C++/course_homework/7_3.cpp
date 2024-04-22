// 查阅资料，对冒泡算法进行改进，使之在新一轮比较中，若没有发生元素交换，则认为已排序完毕。
// 使用改进的冒泡算法，对数组int a = {34，91，83，56，29，93，56，12，88，72} 进行从小到大的排序。
#include <iostream>
using namespace std;
void BubbleSort(int arr[],int len)
{
    bool flag = 0;
    for (int i = 0; i < len - 1;i++)
    {
        flag = 1;
        for (int j = 0; j < len - i - 1;j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                flag = 0;
            }
        }
        if (flag)
        {
            break;
        }
    }
}
int main()
{
    int arr[11] = {34, 9, 1, 83, 56, 29, 93, 56, 12, 88, 72};
    int len = sizeof(arr) / sizeof(arr[0]);
    BubbleSort(arr, len);
    for (int i = 0; i < 11;i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
