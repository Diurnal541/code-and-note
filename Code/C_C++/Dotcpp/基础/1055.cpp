#include <iostream>
using namespace std;
int main(){
	int dec = 0,oct = 0,a = 0,b = 1;
	cin >> dec;
	while (dec != 0){
		a = dec % 8;
		dec /= 8;
		oct += a * b;
		b *= 10;
	}
	cout << oct << endl;
	return 0;
}
