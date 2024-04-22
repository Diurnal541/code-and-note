#include <iostream>
#include <string>
using namespace std;
int main()
{
	char a[80];
	cin.getline(a,80);
	char *p = a;
	int count = 0;
	while (*p != '\0')
	{
		if (*p == ' ')
		{
			count++;
		}
		p++;
	}
	cout << count+1 << endl;
	return 0;
}

