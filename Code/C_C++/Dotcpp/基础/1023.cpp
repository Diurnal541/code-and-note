#include <iostream>
using namespace std;
void selectsort(int[],int);
int main()
{
	int arr[10];
	int len = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0;i < len;i++)
	{
		cin >> arr[i];
	}
	selectsort(arr,len);
	for (int i = 0;i < len;i++)
	{
		cout << arr[i] << endl;
	}
	return 0;
}
void selectsort(int arr[],int len)
{
	int start = 0,end = len - 1;
	while (start < end)
	{
		int max = start;
		int min = start;
		for (int i = start;i <= end;i++)
		{
			if (arr[max] < arr[i])
			{
				max = i;
			}
			if (arr[min] > arr[i])
			{
				min = i;
			}
		}
		int temp = arr[min];
		arr[min] = arr[start];
		arr[start] = temp;
		if (start == max)
		{
			max = min;
		}
		temp = arr[max];
		arr[max] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}
