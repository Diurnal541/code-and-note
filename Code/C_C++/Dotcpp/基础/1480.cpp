#include <iostream>
using namespace std;
int main()
{
	int a,b,sum;
	char c;
	cin >> a >> b >> c;
	switch (c)
	{
		case '+':
			sum = a + b;
			break;
		case '-':
			sum = a - b;
			break;
		case '*':
			sum = a * b;
			break;
		case '/':
			sum = a / b;
			break;
		case '%':
			sum = a % b;
			break;
	}
	cout << sum << endl;
	return 0;
}

