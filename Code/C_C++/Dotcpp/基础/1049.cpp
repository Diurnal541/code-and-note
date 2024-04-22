#include <iostream>
using namespace std;
bool check(int y){
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)){
		return true;
	}
	else{
		return false;
	}
}
int y,m,d,s;
int main(){
	cin >> y >> m >> d;
	if (check(y)){
		for (int i = 1;i <= m - 1;i++){
			if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12){
				s += 31;
			}
			else if (i == 2){
				s += 29;
			}
			else{
				s += 30;
			}
		}
		s += d;
	}
	else {
		for (int i = 1;i <= m - 1;i++){
			if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12){
				s += 31;
			}
			else if (i == 2){
				s += 28;
			}
			else{
				s += 30;
			}
		}
		s += d;
	}
	cout << s << endl;
	return 0;
}


//*********题解***********


//#include<iostream>
//using namespace std;
////定义日期结构体
//struct Date
//{
//    int year;
//    int month;
//    int day;
//};
//int main()
//{
//    //定义结构体变量
//    Date date;
//    //定义sum保存天数
//    int sum=0;
//    //用数组保存平年12个月每个人月的天数
//    int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//    //输入日期年月日
//    cin>>date.year;
//    cin>>date.month;
//    cin>>date.day;
//    //判断是否是闰年
//    if(date.year%4==0&&date.year%100!=0||date.year%400==0)
//    {
//        mon[1]=29;
//    }
//    //计算输入的日期是该年的第几天
//    for(int i=0;i<date.month-1;i++)
//    {
//        sum+=mon[i];
//    }
//    sum+=date.day;
//    cout<<sum;
//    return 0;
//}
