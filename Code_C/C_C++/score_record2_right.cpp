#include <iostream>
#include <string>
using namespace std;
// ����ѧ���ṹ��
struct Student
{
    string Id;
    string Name;
    double Ane_score;
    double Two_score;
    double Three_score;
    double Sum_score;
};
int main()
{
    int N;
    cin >> N;
    Student student[N];
    double Ane_sum = 0;
    double Two_sum = 0;
    double Three_sum = 0;
    int i;
    // ����ѧ����Ϣ
    for (i = 0; i < N; i++)
    {
        cin >> student[i].Id;
        cin >> student[i].Name;
        cin >> student[i].Ane_score;
        cin >> student[i].Two_score;
        cin >> student[i].Three_score;
    }
    // ��ÿ�ųɼ����ܳɼ���ÿ��ѧ�����ܳɼ�
    for (i = 0; i < N; i++)
    {
        Ane_sum += student[i].Ane_score;
        Two_sum += student[i].Two_score;
        Three_sum += student[i].Three_score;
        student[i].Sum_score = student[i].Ane_score + student[i].Two_score + student[i].Three_score;
    }
    // �����µı�������ÿ�ųɼ���ƽ���ɼ�
    double Ane_aver = Ane_sum / N;
    double Two_aver = Two_sum / N;
    double Three_aver = Three_sum / N;
    // ���ÿ�ſε�ƽ���ɼ�
    cout << Ane_aver << " "
         << Two_aver << " "
         << Three_aver << endl;
    // �ҵ�������ߵ�ͬѧ
    for (i = 1; i < N; i++)
    {
        if (student[0].Sum_score < student[i].Sum_score)
        {
            student[0].Id = student[i].Id;
            student[0].Name = student[i].Name;
            student[0].Ane_score = student[i].Ane_score;
            student[0].Two_score = student[i].Two_score;
            student[0].Three_score = student[i].Three_score;
            student[0].Sum_score = student[i].Sum_score;
        }
    }
    // �����߷���ͬѧ�ĸ�����Ϣ
    cout << student[0].Id << " "
         << student[0].Name << " "
         << student[0].Ane_score << " "
         << student[0].Two_score << " "
         << student[0].Three_score << endl;
    return 0;
}