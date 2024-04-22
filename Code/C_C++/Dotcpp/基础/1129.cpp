#include <iostream>
using namespace std;
int main()
{
	int a[10];
	for (int i = 0;i < 10;i++)
	{
		cin >> a[i];
	}
	for (int i = 0;i < 9;i++)
	{
		int flag = 0;
		for (int j = 0;j < 9 - i;j++)
		{
			if (a[j] < a[j + 1])
			{
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
	for (int i = 0;i < 10;i++)
	{
		cout << a[i] << " ";
	} 
	return 0;
} 

