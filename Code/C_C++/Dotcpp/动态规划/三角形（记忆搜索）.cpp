#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int T,n;
int arr[N][N];
int mem[N][N];
int dps(int x,int y){
	if (mem[x][y]){
		return mem[x][y];
	}
	int sum = 0;
	if (x > n || y > n){
		sum = 0;
	}
	else{
		sum = max(dps(x + 1,y),dps(x + 1,y + 1)) + arr[x][y];
	}
	mem[x][y] = sum;
	return sum;
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
