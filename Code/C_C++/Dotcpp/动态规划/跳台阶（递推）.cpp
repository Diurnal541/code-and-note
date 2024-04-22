#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int n;
int f[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	f[1] = 1,f[2] = 2;
	cin >> n;
	for (int i = 3;i <= n;i++){
		f[i] = f[i - 1] + f[i - 2];
	}
	cout << f[n] << endl;
	return 0;
}
