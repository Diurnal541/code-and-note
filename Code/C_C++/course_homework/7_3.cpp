// �������ϣ���ð���㷨���иĽ���ʹ֮����һ�ֱȽ��У���û�з���Ԫ�ؽ���������Ϊ��������ϡ�
// ʹ�øĽ���ð���㷨��������int a = {34��91��83��56��29��93��56��12��88��72} ���д�С���������
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
