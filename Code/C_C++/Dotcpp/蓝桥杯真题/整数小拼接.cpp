#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n,k,arr[N];
int ans;
int main(){
	cin >> n >> k;
	for (int i = 1;i <= n;i++){
		cin >> arr[i];
	}
	for (int i = 1;i <= n;i++){
		for (int j = 1;j <= n;j++){
			if (i == j){
				continue;
			}
			if (arr[i] * (long long)pow(10,int(log10(arr[j]) + 1)) + arr[j] <= k){
				ans++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
