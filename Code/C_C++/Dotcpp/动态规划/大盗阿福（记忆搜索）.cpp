//要是想实现记忆化搜索的话，那么dfs的参数就需要尽可能的少
//不应该把没有影响到边界的参数放进来
#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int f[N],mem[N];
int n,T;
int dfs(int x){
	if (mem[x]){
		return mem[x];
	}
	int sum = 0;
	if (x > n){
		sum = 0;
	}
	else{
		sum = max(dfs(x + 1),dfs(x + 2) + f[x]);
	}
	mem[x] = sum;
	return sum;
}
int main(){
	cin >> T;
	while (T--){
		cin >> n;
		for (int i = 1;i <= n;i++){
			cin >> f[i];
		}
		memset(mem,0,sizeof mem);
		int ans = dfs(1);
		cout << ans << endl;
	}
	return 0;
}
