#include <iostream>
using namespace std;
int max_gys(int a,int b){
	if (b == 0){
		return a;
	}
	return max_gys(b, a % b);
}
int min_gbs(int a,int b){
	return (a * b) / max_gys(a,b);
}
int main(){
	int a,b;
	cin >> a >> b;
	cout << max_gys(a,b) << " " << min_gbs(a,b) << endl;
	return 0;
}
