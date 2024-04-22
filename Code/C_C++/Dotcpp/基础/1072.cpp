#include <iostream>
using namespace std;
int main(){
	int n = 0;
	while ((cin >> n) && n){
		int ans = 0;
		while (n >= 2){
			if (n >= 3){
				int temp = n / 3;
				ans += temp;
				n = n - temp * 3 + temp;
			}
			else if (n == 2){
				ans++;
				n = 0;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
