// ��֪����an��a1=2,�������¹�ϵ : an = an-1 * 3 + 7
// 1��ʹ��һά�����̣����ڼ�¼1 - 100���ֵ��
// 2��ʹ��ѭ���������a [0]��a[9]��a[19]��a[29]��a[39]��a[49]��a[59]��a[69]��a[79]��a[89]��a[99] ��ֵ��
#include <iostream>
using namespace std;
int main()
{
    double arr[100];
    arr[0] = 2;
    for (int i = 1; i < 100;i++)
    {
        arr[i] = arr[i - 1] * 3 + 7;
    }
    for (int i = 0; i < 100;i++)
    {
        if (i == 0 || i % 10 == 9)
        {
            cout << "arr[" << i << "]" << " = " << arr[i] << endl;
        }
    }
    return 0;
}
