#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n,m;
int w[N],v[N];
int res = 0;
void dfs(int x,int sumV,int sumW){
	if (x > n){
		if (sumV <= m && sumW >= res){
			res = sumW;
		}
		return;
	}
	dfs(x + 1,sumV,sumW);
	if (sumV + v[x] <= m){
		dfs(x + 1,sumV + v[x],sumW + w[x]);
	}
}
int main(){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> v[i] >> w[i];
	}
	dfs(1,0,0);
	cout << res << endl;
	return 0;
}
