// ���岢��ʼ��һ��һά��ʵ�����飬���ڴ�Ű༶����ѧ���ġ��ṹ��������ơ���ĩ���Գɼ���Ҫ��
// 1���������ÿһ��ѧ���ġ��ṹ��������ơ��ɼ���
// 2�����Ҳ������͡��ṹ��������ơ��ɼ������±�����ֵ��
// 3�����㲢���ƽ�����ṹ��������ơ��ɼ���
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;
int main()
{
    int n;
    cout << "������༶����:";
    cin >> n;
    int arr[n];
    srand(time(0));
    for (int i = 0; i < n;i++)
    {
        int num = rand() % 100 + 1;
        arr[i] = num;
    }
    for (int i = 0; i < n;i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    int min = arr[0];
    for (int i = 0; i < n;i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }
    for (int i = 0; i < n;i++)
    {
        if (min == arr[i])
        {
            cout << "�ɼ����Ϊ:" << min << endl
                 << "���±�����Ϊ:" << i << endl;
            break;
        }
    }
    double s = 0.0;
    for (int i = 0; i < n;i++)
    {
        s += arr[i];
    }
    double average = static_cast<double>(s) / n;
    cout << "ƽ����Ϊ:" << fixed << setprecision(2) << average << endl;
    return 0;
}
