#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 10010;
int N,M,res;
vector<int>arr;
bool check(int x){
	int count = 1,sum = 0,pos = 0;
	while (pos < N){
		if (sum + arr[pos] > x){
			count++;
			sum = 0;
		}
		else {
			sum += arr[pos];
			pos++;
		}
	}
	return count <= M;
}
int main(){
	cin >> N >> M;
	int num,max_num = 0,total_num = 0;
	for (int i = 0;i < N;i++){
		cin >> num;
		arr.push_back(num);
		max_num = max(num,max_num);
		total_num += num;
	}
	int left = max_num,right = total_num;
	while (left <= right){
		int mid = (left + right) / 2;
		if (check(mid)){
			res = mid;
			right = mid - 1;	
		}
		else {
			left = mid + 1;
		}
	}
	cout << res << endl;
	return 0;
}
