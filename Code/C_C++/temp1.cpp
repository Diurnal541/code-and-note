#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	string str1, str2;
	getline(cin, str1);
	getline(cin, str2);
	sort(str1.begin(), str1.end());
	sort(str2.begin(), str2.end());
	int diff = abs(stoi(str1) - stoi(str2));
	char result = static_cast<char>(diff);
	cout << result << endl;

	return 0;
}