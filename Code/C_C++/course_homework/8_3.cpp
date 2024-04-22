#include <iostream>
using namespace std;
double *sum()
{
    double *p = new double[20];
    //double *p = (double *)malloc(20 * sizeof(double));
    p[0] = 1.5;
    for (int i = 1; i < 20;i++)
    {
        p[i] = p[i - 1] * 3 + 1.5;
    }
    return p;
}
int main()
{
    double *p = sum();
    for (int i = 0; i < 20;i++)
    {
        cout << p[i] << endl;
    }
    //free(p);
    delete[] p;
    return 0;
}
// 申请不到堆内存的情况：在分配内存时，没有分配足够的内存，比如第五行中括号里的数字小于20
// 计算机内存不足，即可用内存已经全部耗尽
// 内存泄露，已分配的内存没有被正确释放，导致堆内存被占用，从而无法申请新的内存
