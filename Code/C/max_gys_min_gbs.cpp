#include <stdio.h>
#include <stdlib.h>
int max_gys(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	return max_gys(b, a % b);
}

int min_gbs(int a, int b)
{
	return (a * b) / max_gys(a, b);
}

int main()
{
	int a, b;
	scanf_s("%d%d", &a, &b);
	int x = max_gys(a, b);
	int y = min_gbs(a, b);
	printf("%d %d\n", x, y);
	system("pause");
	return 0;
}