#include <iostream>
using namespace std;
#define can(a,b) t = a,a = b,b = t;
int main(){
	int a,b,t;
	cin >> a >> b;
	can(a,b);
	cout << a << " " << b;
	return 0;
}
