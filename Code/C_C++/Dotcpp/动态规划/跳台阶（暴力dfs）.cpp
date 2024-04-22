//一个楼梯共有n级台阶，每次可以走一级或者两级，问从第0级台阶走到第n级台阶一共有多少种方案
#include <bits/stdc++.h>
using namespace std;
int dfs(int x){
	if (x == 1){
		return 1;
	}
	else if (x == 2){
		return 2;
	}
	else{
		return dfs(x - 1) + dfs(x - 2);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	int ans = dfs(n);
	cout << ans << endl;
	return 0;
}
