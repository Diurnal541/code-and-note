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
//����һ�����飬��������ʱ�����ִ������飬�±�Ϊ�����ֵľ���ֵ�����磺���� -5 ������ a [ 5 ] = -5
//���ʱ���ж������±��Ƿ����λ�ô�������ֵľ���ֵ��ȣ��������
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

