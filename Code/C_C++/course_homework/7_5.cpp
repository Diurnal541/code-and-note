//����һ����ά���飬���ڴ洢5��ѧ���Ŀγ̳ɼ���ÿ��ѧ���и�����Ӣ��ṹ��������ơ���ѧ����4�ſγ̡�
//1)ͨ����ά�����ʼ���ķ�ʽ�洢ѧ���ĸ��ſγ̳ɼ���
//2)�����3��ѧ����ƽ���ɼ���
//3)�����̻���I�γ̵�ƽ���ɼ���
#include <iostream>
using namespace std;
int main()
{
    int arr[5][4] =
        {
            {84, 68, 91, 73},
            {76, 79, 87, 94},
            {66, 82, 69, 88},
            {95, 67, 72, 78},
            {75, 81, 64, 83}
        };
    int i, j, s1 = 0, s2 = 0;
    double avg3;
    for (i = 2, j = 0; j < 4;j++)
    {
        s1 += arr[i][j];
    }
    avg3 = static_cast<double>(s1) / 4;
    cout << avg3 << endl;
    double avg;
    for (i = 0, j = 2; i < 5;i++)
    {
        s2 += arr[i][j];
    }
    avg = static_cast<double>(s2) / 5;
    cout << avg << endl;
    return 0;
}
