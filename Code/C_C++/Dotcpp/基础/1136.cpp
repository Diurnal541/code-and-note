#include <iostream>
using namespace std;
int main()
{
	for (int i = 1000;i < 10000;i++)
	{
		int j = (i % 100) + (i / 100);
		if (j * j == i)
		{
			cout << i << endl;
		}
	}
	return 0;
 } 
 
