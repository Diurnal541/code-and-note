#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n,m;
int v[N],w[N];
int dp[N][N];

int main(){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> v[i] >> w[i];
	}
	for (int i = n;i >= 1;i--){
		for (int j = 0;j <= m;j++){
			if (j < v[i]){
				dp[i][j] = dp[i + 1][j];
			}
			else {
				dp[i][j] = max(dp[i + 1][j],dp[i + 1][j - v[i]] + w[i]);
			}
		}
	}
	cout << dp[1][m] << endl;
	return 0;
}
