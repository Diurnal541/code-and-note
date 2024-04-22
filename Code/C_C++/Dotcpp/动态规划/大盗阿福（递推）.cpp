#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n,T;
int f[N];
int dp[N];
int main(){
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1;i <= n;i++){
			cin >> f[i];
		}
		memset(dp,0,sizeof dp);
		for (int i = 1;i <= n;i++){
			dp[i] = max(dp[i - 1],dp[i - 2] + f[i]);
		}
//		for (int i = n;i >= 1;i--){
//			dp[i] = max(dp[i + 1],dp[i + 2] + f[i]);
//		}
//		或
//		int newf = 0,temp1 = 0,temp2 = 0;
//		for (int i = 1;i <= n;i++){
//			newf = max(temp1,temp2 + f[i]);
//			temp2 = temp1;
//			temp1 = newf;
//		}
//		cout << newf << endl;
		cout << dp[n] << endl;
	}
	return 0;
}
