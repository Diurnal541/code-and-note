#include<iostream>
#include<iomanip>  //输出小数位所需头文件
using namespace std;
int main()
{
    float F,C; //定义两个浮点数
    cin>>F;   //输入摄氏温度
    C=5*(F-32)/9;  //计算华氏温度
    cout<<fixed<<setprecision(2)<<C<<endl; 
    //输出含两位小数的华氏温度（此步骤也可分开写：cout<<fixed<<setprecision(2)；//保留两位小数cout<<C<<endl;//输出）
    return 0;
}
