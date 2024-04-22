// 题目 1068: 二级C语言-温度转换
#include <iostream>
using namespace std;
int ctof(int c)
{
    return c * 9 / 5 + 32;
}
int main()
{
    for (int i = -100; i < 151; i += 5)
    {
        cout << "c=" << i << "->f=" << ctof(i) << endl;
    }
    return 0;
}
