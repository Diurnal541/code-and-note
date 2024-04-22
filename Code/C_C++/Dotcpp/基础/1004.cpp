#include <stdio.h>
using namespace std;
int cow(int);
int main()
{
	int n;
	while ((scanf("%d",&n)) && n)
	{
		printf("%d\n",cow(n));
	}
	return 0;
}
int cow(int n)
{
	if (n <= 3)
	{
		return n;
	}
	else
	{
		return cow(n - 1) + cow(n - 3);
	}
}
