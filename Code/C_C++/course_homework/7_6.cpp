//5��ѧ����ÿ��ѧ����4�ſΣ��Ȱ�������Ҫ��������������Ȼ�����������е���������������
//1)�ҳ��ɼ���ߵ�ѧ����źͿγ̡�
//2)�ҳ�������γ̵�ѧ����ż�����ſε�ȫ���ɼ���
//3)��ȫ��ѧ�����ſγ̵�ƽ���������������
#include <iostream>
using namespace std;
void sear_max(int arr[][4],int stu_num)
{
    int i, j, max_stu_score = 0, max_stu_index = 0, max_course_score = 0, max_course_index = 0;
    for (i = 0; i < stu_num;i++)
    {
        int total_score = 0;
        for (j = 0; j < 4;j++)
        {
            total_score += arr[i][j];
        }
        if (total_score > max_stu_score)
        {
            max_stu_score = total_score;
            max_stu_index = i;
        }
    }
    cout << "�ɼ���ߵ�ͬѧ�������:" << max_stu_index + 1 << endl;
    for (j = 0; j < 4; j++)
    {
        int total_score = 0;
        for (i = 0; i < stu_num; i++)
        {
            total_score += arr[i][j];
        }
        if (total_score > max_course_score)
        {
            max_course_score = total_score;
            max_course_index = j;
        }
    }
    switch(max_course_index)
    {
        case 0:
            cout << "�ɼ���ߵĿγ��Ǹ���" << endl;
            break;
        case 1:
            cout << "�ɼ���ߵĿγ���Ӣ��" << endl;
            break;
        case 2:
            cout << "�ɼ���ߵĿγ��ǽṹ���������" << endl;
            break;
        case 3:
            cout << "�ɼ���ߵĿγ��Ǵ�ѧ����" << endl;
            break;
        default:
            break;
    }
}
void sear_fail(int arr[][4],int stu_num)
{
    for (int j = 0; j < 4;j++)
    {
        for (int i = 0; i < stu_num;i++)
        {
            if (arr[i][j] < 60)
            {
                switch(j)
                {
                    case 0:
                        cout << "ѧ��" << i + 1 << "�ĸ����ɼ�������" << endl;
                        break;
                    case 1:
                        cout << "ѧ��" << i + 1 << "��Ӣ��ɼ�������" << endl;
                        break;
                    case 2:
                        cout << "ѧ��" << i + 1 << "�Ľṹ��������Ʋ�����" << endl;
                        break;
                    case 3:
                        cout << "ѧ��" << i + 1 << "�Ĵ�ѧ��������" << endl;
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
void avg(int arr[][4],int stu_num)
{
    double average = 0;
    for (int i = 0; i < stu_num;i++)
    {
        int total_score = 0;
        for (int j = 0; j < 4;j++)
        {
            total_score += arr[i][j];
        }
        average = static_cast<double>(total_score) / 4;
        cout << "ѧ��" << i + 1 << "ƽ���ɼ�Ϊ:" << average << endl;
    }
}
int main()
{
    int arr[5][4] =
        {
            {42, 55, 67, 83},//247
            {76, 61, 49, 72},//258
            {89, 43, 58, 69},//259
            {54, 81, 47, 65},//247
            {62, 78, 44, 50}//234
        //  323 318  265 339
        };
    sear_max(arr, 5);
    cout << endl;
    sear_fail(arr, 5);
    cout << endl;
    avg(arr, 5);
    return 0;
}
