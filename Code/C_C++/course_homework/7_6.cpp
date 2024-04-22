//5个学生，每个学生有4门课，先按照下列要求定义三个函数，然后在主函数中调用这三个函数。
//1)找出成绩最高的学生序号和课程。
//2)找出不及格课程的学生序号及其各门课的全部成绩。
//3)求全部学生各门课程的平均分数，并输出。
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
    cout << "成绩最高的同学的序号是:" << max_stu_index + 1 << endl;
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
            cout << "成绩最高的课程是高数" << endl;
            break;
        case 1:
            cout << "成绩最高的课程是英语" << endl;
            break;
        case 2:
            cout << "成绩最高的课程是结构化程序设计" << endl;
            break;
        case 3:
            cout << "成绩最高的课程是大学物理" << endl;
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
                        cout << "学生" << i + 1 << "的高数成绩不及格" << endl;
                        break;
                    case 1:
                        cout << "学生" << i + 1 << "的英语成绩不及格" << endl;
                        break;
                    case 2:
                        cout << "学生" << i + 1 << "的结构化程序设计不及格" << endl;
                        break;
                    case 3:
                        cout << "学生" << i + 1 << "的大学物理不及格" << endl;
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
        cout << "学生" << i + 1 << "平均成绩为:" << average << endl;
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
