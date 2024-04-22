#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define Area(s,a,b,c) area = sqrt(s * (s - a) * (s - b) * (s - c));
#define S(a,b,c) s = (a + b + c) / 2.0;
int main(){
	int a,b,c;
	cin >> a >> b >> c;
	double s,area;
	S(a,b,c);
	Area(s,a,b,c);
	cout << fixed << setprecision(3) << area << endl;
	return 0;
}
