#include <bits/stdc++.h>
using namespace std;
int ma, ca, ea, mz, cz, ez;
struct score
{
    int m;
    int c;
    int e;
};
struct student
{
    string num;
    string name;
    struct score sco;
};
void input(int n, student stu[])
{
    for (int i = 0; i < n; i++)
    {
        cin >> stu[i].num >> stu[i].name >> stu[i].sco.m >> stu[i].sco.c >> stu[i].sco.e;
    }
}
int averarge(int n,student stu[])
{
    for (int i = 0; i < n;i++)
    {
        mz += stu[i].sco.m;
        cz += stu[i].sco.c;
        ez += stu[i].sco.e;
    }
    ma = mz / n;
    ca = cz / n;
    ea = ez / n;
    return ma, ca, ea;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int s[100];
    student stu[100];
    input(n, stu);
    ma, ca, ea = averarge(n, stu);
    for (int i = 0; i < n;i++)
    {
        s[i] = stu[i].sco.m + stu[i].sco.c + stu[i].sco.e;
    }
    int max = 0;
    for (int i = 0; i < n;i++)
    {
        if (s[i] > s[max])
        {
            s[max] = s[i];
        }
    }
    cout << ma << " " << ca << " " << ea << endl
         << stu[max].num << " " << stu[max].name << " " << stu[max].sco.m << " " << stu[max].sco.c << " " << stu[max].sco.e;
    return 0;
}
