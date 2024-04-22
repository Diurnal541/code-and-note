#include <bits/stdc++.h>
using namespace std;
int n;
const int N = 20;
int mem[N];
int dfs(int x){
	if (mem[x]){
		return mem[x];
	}
	int sum = 0;
	if (x == 1){
		sum = 1;
	}
	else if (x == 2){
		sum = 2;
	}
	else{
		sum = dfs(x - 1) + dfs(x - 2);
	}
	mem[x] = sum;
	return sum;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	int ans = dfs(n);
	cout << ans << endl;
	return 0;
}
