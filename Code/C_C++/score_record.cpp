#include <bits/stdc++.h>
using namespace std;
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
void input(int n,student stu[])
{
    for (int i = 0; i < n; i++)
    {
        cin >> stu[i].num >> stu[i].name >> stu[i].sco.m >> stu[i].sco.c >> stu[i].sco.e;
    }
}
void print(int n,student stu[])
{
    for (int i = 0; i < n;i++)
    {
        cout << stu[i].num << "," << stu[i].name << "," << stu[i].sco.m << "," << stu[i].sco.c << "," << stu[i].sco.e << endl;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    student stu[100];
    input(n, stu);
    print(n, stu);
    return 0;
}
