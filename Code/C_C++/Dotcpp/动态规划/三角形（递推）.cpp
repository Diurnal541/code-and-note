#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n,T;
int arr[N][N],dp[N][N];
int main(){
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= i;j++){
				cin >> arr[i][j];
			}
		}
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= i;j++){
				dp[i][j] = max(dp[i - 1][j],dp[i - 1][j - 1]) + arr[i][j];
			}
		}
		int ans = 0;
		for (int i = 1;i <= n;i++){
			ans = max(dp[n][i],ans);
		}
		cout << ans << endl;
	}
	return 0;
}
