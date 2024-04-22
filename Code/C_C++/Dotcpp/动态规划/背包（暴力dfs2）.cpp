#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n,m,res = 0;
int v[N],w[N];
int dfs(int x,int spV){
	if (x > n){
		return 0;
	}
	else if (spV < v[x]){
		return dfs(x + 1,spV);
	}
	else if (spV >= v[x]){
		return max(dfs(x + 1,spV),dfs(x + 1,spV - v[x]) + w[x]);
	}
}
int main(){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		cin >> v[i] >> w[i];
	}
	res = dfs(1,m);
	cout << res << endl;
	return 0;
}
