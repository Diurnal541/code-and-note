/*1.从第一个元素开始，该元素可以认为已经被排序。
2.取下一个元素存入临时变量temp，对前方有序序列从后往前扫描。
3.如果该元素大于temp，则将该元素移到下一位。
4.重复步骤3，直到找到已于等于temp的元素。
5.temp插入到该元素的后面一位，如果所有有序元素都大于temp，则将temp插入到下标为0的位置（既数组的首位，说明该元素是目前最小的元素）。
6.重复以上的2~5步骤，直至操作完整个数组中的所有元素。
*/
void insertsort(int arr[], int len)
{
	int j;
	for (j = 0; j < len - 1; j++)
	{
		int end = j; //前end位为有序部分
		int temp = arr[j + 1]; //设置临时变量
		while (end >= 0)
		{
			if (arr[end] > temp) //将temp变量与前一位元素比较
			{
				arr[end + 1] = arr[end]; //将比temp变量大的元素向后移一位
				end--;
			}
			else
			{
				break;
			}
		}
		arr[end + 1] = temp; //将temp变量插入有序数组中
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