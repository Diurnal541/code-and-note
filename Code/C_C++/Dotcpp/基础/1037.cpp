#include <iostream>
using namespace std;
#define hong(a,b) a %= b;
int main(){
	int a,b;
	cin >> a >> b;
	hong(a,b);
	cout << a << endl;
	return 0;
}
