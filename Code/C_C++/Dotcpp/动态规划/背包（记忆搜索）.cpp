#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n,m,res = 0;
int v[N],w[N];
int mem[N][N];
int dfs(int x,int spV){
	if (mem[x][spV]){
		return mem[x][spV];
	}
	int sum = 0;
	if (x > n){
		sum = 0;
	}
	else if (spV < v[x]){
		sum = dfs(x + 1,spV);
	}
	else if (spV >= v[x]){
		sum = max(dfs(x + 1,spV),dfs(x + 1,spV - v[x]) + w[x]);
	}
	mem[x][spV] = sum;
	return sum;
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
