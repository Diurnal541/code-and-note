/*1.�ӵ�һ��Ԫ�ؿ�ʼ����Ԫ�ؿ�����Ϊ�Ѿ�������
2.ȡ��һ��Ԫ�ش�����ʱ����temp����ǰ���������дӺ���ǰɨ�衣
3.�����Ԫ�ش���temp���򽫸�Ԫ���Ƶ���һλ��
4.�ظ�����3��ֱ���ҵ����ڵ���temp��Ԫ�ء�
5.temp���뵽��Ԫ�صĺ���һλ�������������Ԫ�ض�����temp����temp���뵽�±�Ϊ0��λ�ã����������λ��˵����Ԫ����Ŀǰ��С��Ԫ�أ���
6.�ظ����ϵ�2~5���裬ֱ�����������������е�����Ԫ�ء�
*/
void insertsort(int arr[], int len)
{
	int j;
	for (j = 0; j < len - 1; j++)
	{
		int end = j; //ǰendλΪ���򲿷�
		int temp = arr[j + 1]; //������ʱ����
		while (end >= 0)
		{
			if (arr[end] > temp) //��temp������ǰһλԪ�رȽ�
			{
				arr[end + 1] = arr[end]; //����temp�������Ԫ�������һλ
				end--;
			}
			else
			{
				break;
			}
		}
		arr[end + 1] = temp; //��temp������������������
	}
}

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int arr[10] = { 2, 7, 6, 8, 5, 9, 1, 3, 4, 10 };
	int len = sizeof(arr) / sizeof(arr[0]);
	insertsort(arr, len);
	for (int i = 0; i < len; i++)
	{
		printf("%d\n", arr[i]);
	}
	system("pause");
	return 0;
}