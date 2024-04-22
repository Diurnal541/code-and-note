//#include <iostream>
//#include <cmath>
//using namespace std;
//void bubble(int[],int);
//int main()
//{
//	int n;
//	while (cin >> n)
//	{
//		if (n == 0)
//		{
//			break;
//		}
//		else
//		{
//			int a[n];
//			for (int i = 0;i < n;i++)
//			{
//				cin >> a[i];  
//			}
//			bubble(a,n);
//			for (int i = 0;i < n;i++)
//			{
//				cout << a[i] << " ";
//			}
//			cout << endl; 
//		}
//	}
//	return 0;
//}
//void bubble(int arr[],int len)
//{
//	for (int i = 0;i < len - 1;i++)
//	{
//		int flag = 0;
//		for (int j = 0;j < len - 1 - i;j++)
//		{
//			if (abs(arr[j]) < abs(arr[j + 1]))
//			{
//				int temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//				flag = 1;
//			}
//		}
//		if (flag == 0)
//		{
//			break;
//		}
//	}
//}
//定义一个数组，输入数字时将数字存入数组，下标为该数字的绝对值，例如：输入 -5 ，则令 a [ 5 ] = -5
//输出时，判断数组下标是否与该位置储存的数字的绝对值相等，是则输出
#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int n,x;
	while (cin >> n && n)
	{
		int a[100] = {-1};
		for (int i = 0;i < n;i++)
		{
			cin >> x;
			a[abs(x)] = x;
		}
		for (int i = 99;i >= 0;i--)
		{
			if (i == abs(a[i]))
			{
				cout << a[i] << " ";
			}
		}
		cout << endl;
	}
	return 0;
}

