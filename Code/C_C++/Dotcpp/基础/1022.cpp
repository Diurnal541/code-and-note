#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int N;
	cin >> N;
	for (int i = 2; i < N; i++)
	{
		bool prime = true;
		for (int j = 2; j <= sqrt(i); j++)
		{
			if (i % j == 0)
			{
				prime = false;
				break;
			}
		}
		if (prime)
		{
			cout << i << endl;
		}
	}
	return 0;
}

