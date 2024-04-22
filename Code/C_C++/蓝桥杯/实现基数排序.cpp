#include <iostream>
#include<string>
#include<cstring>
using namespace std;
int main()
{
  int num,max=0;
  int array[110];
  int bucket[10][110];  // 桶
  int number[10]; // 统计每个桶存放的数字的数量
  memset(number,0,10);
  scanf("%d",&num);
  // 输入的时候找出最大值
  for(int i=0;i<num;i++)
  {
    scanf("%d",&array[i]);
    if(array[i]>max) max=array[i];
  }
  // 将int转换为string，求其位数
  int maxlength = std::to_string(max).length();
  for(int i=0,n=1;i<maxlength;i++,n*=10)
  {
    // 将数据根据除以n后的个位数，存进不同的桶里面
    for(int j=0;j<num;j++)
    {
      int digit = array[j]/n%10;
      bucket[digit][number[digit]] = array[j];
      number[digit]++;
    }

    int index=0;
    // 将数据重新从桶里面装入数组
    for(int j=0;j<10;j++)
    {
      // 只有桶中有数据才进行操作
      if(number[j]!=0)
      {
        for(int k=0;k<number[j];k++)
        {
          array[index++] = bucket[j][k];
        }
        // 将计数清零
        number[j]=0;
      }
    }

  }

  for(int i=0;i<num;i++)
  {
    printf("%d ",array[i]);
  }
  return 0;
}