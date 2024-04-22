#include <iostream>
#include <cmath>
using namespace std;
bool isprime(int x){
	if (x == 2){
		return true;
	}
	else if (x == 0 || x == 1){
		return false;
	}
	for (int i = 2;i <= sqrt(x);i++){
		if (x % i == 0){
			return false;
		}
	}
	return true;
}
int main(){
	int m,n,sum = 0;
	cin >> m >> n;
	for (int i = m;i <= n;i++){
		if (isprime(i)){
			sum += i;
		}
		else{
			continue;
		}
	}
	cout << sum << endl;
	return 0;
}
