#include <iostream>
using namespace std;
int max_gys(int a, int b) {
	if (b == 0)
	{
		return a;
	}
	return max_gys(b, a % b);
}
int min_gbs(int a, int b) {
	return (a * b) / max_gys(a, b);
}
int main() {
	int m,n;
	cin >> m >> n;
	cout << max_gys(m,n) << endl << min_gbs(m,n) << endl;
	return 0;
}
