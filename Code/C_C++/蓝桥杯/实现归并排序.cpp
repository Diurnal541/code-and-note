#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;
void merge(int* a, int low, int mid, int hight)  //�ϲ�����
{
	int* b = new int[hight - low + 1];  //�� new ����һ����������
	int i = low, j = mid + 1, k = 0;    // kΪ b �����С��
	while (i <= mid && j <= hight)  
	{
		if (a[i] <= a[j])
		{
			b[k++] = a[i++];  //����С�������� b ��������
		}
		else
		{
			b[k++] = a[j++];
		}
	}
	while (i <= mid)  // j ���н�������ʣ��� i ���в����� b ������ 
	{
		b[k++] = a[i++];
	}
	while (j <= hight)// i ���н�������ʣ��� j ���в����� b ������ 
	{
		b[k++] = a[j++];
	}
	k = 0;  //��С��Ϊ 0 ��ʼ����
	for (int i = low; i <= hight; i++)  //�� b �����ֵ���ݸ����� a
	{
		a[i] = b[k++];
	}
	delete[]b;     // ������������󣬽���Ŀռ�����ͷţ����٣�
}
void mergesort(int* a, int low, int hight) //�鲢����
{
	if (low < hight)
	{
		int mid = (low + hight) / 2;
		mergesort(a, low, mid);          //�� a[low,mid]��������
		mergesort(a, mid + 1, hight);    //�� a[mid+1,hight]��������
		merge(a, low, mid, hight);       //���кϲ�����
	}
}
int main()
{
	int n, a[100];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	mergesort(a, 0, n-1);
	for (int i = 0; i < n; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
}
