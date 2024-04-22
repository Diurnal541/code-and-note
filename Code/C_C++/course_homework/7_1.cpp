// 定义并初始化一个一维的实型数组，用于存放班级所有学生的《结构化程序设计》期末考试成绩，要求：
// 1）遍历输出每一个学生的《结构化程序设计》成绩；
// 2）查找并输出最低《结构化程序设计》成绩和其下标索引值；
// 3）计算并输出平均《结构化程序设计》成绩。
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;
int main()
{
    int n;
    cout << "请输入班级人数:";
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
            cout << "成绩最差为:" << min << endl
                 << "其下标索引为:" << i << endl;
            break;
        }
    }
    double s = 0.0;
    for (int i = 0; i < n;i++)
    {
        s += arr[i];
    }
    double average = static_cast<double>(s) / n;
    cout << "平均分为:" << fixed << setprecision(2) << average << endl;
    return 0;
}
