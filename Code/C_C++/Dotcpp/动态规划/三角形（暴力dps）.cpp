#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int T,n;
int arr[N][N];
int dps(int x,int y){
	if (x > n || y > n){
		return 0;
	}
	else{
		return max(dps(x + 1,y),dps(x + 1,y + 1)) + arr[x][y];
	}
}
int main(){
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1;i <= n;i++){
			for (int j = 1;j <= i;j++){
				cin >> arr[i][j];
			}
		}
		int ans = dps(1,1);
		cout << ans << endl;
	}
	return 0;
}
