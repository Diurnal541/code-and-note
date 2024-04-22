#include<iostream>
using namespace std;
int main()
{
	int a[4];
	for (int i =0;i < 4;i++)
	{
		cin >> a[i];
	}
	int *p = a;
	for (int i = 0;i < 3;i++)
	{
		int flag = 0; 
		for (int j = 0;j < 3 - i;j++)
		{
			if (*(p + j)> *(p + j + 1))
			{
				int temp = *(p + j);
				*(p + j) = *(p + j + 1);
				*(p + j + 1) = temp;
				flag = 1;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
	for (int i = 0;i < 4;i++)
	{
		cout << a[i] << " ";
	}
	return 0;
}

