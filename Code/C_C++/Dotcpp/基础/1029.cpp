#include <iostream>
#include <cmath>
using namespace std;
bool check(int n){
	if (n == 2){
		return true;
	}
	if (n == 0 || n == 1){
		return false;
	}
	int s = sqrt(n);
	for (int i = 2;i <= s;i++){
		if (n % i == 0){
			return false;
		}
	}
	return true;
}
int main(){
	int n;
	cin >> n;
	if (check(n)){
		cout << "prime" << endl;
	}
	else{
		cout << "not prime" << endl;
	}
	return 0;
}
