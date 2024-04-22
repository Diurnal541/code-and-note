//定义一个二维数组，用于存储5个学生的课程成绩，每个学生有高数、英语、结构化程序设计、大学物理共4门课程。
//1)通过二维数组初始化的方式存储学生的各门课程成绩。
//2)求出第3个学生的平均成绩。
//3)求出编程基础I课程的平均成绩。
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
