#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int n,c;
int arr[N];
int main(){
	cin >> n >> c;
	for (int i = 1;i <= n;i++){
		cin >> arr[i];
	}
	sort(arr + 1,arr + n + 1);
	int left = 0;
	int right = arr[n] - arr[1];
	int result = 0;
	while (left <= right){
		int mid = (left + right) / 2;
		int count = 1;
		int prev = arr[1];
		for (int i = 2;i <= n;i++){   //如果以mid为间隔，那么可以装下count个牛
			if (arr[i] - prev >= mid){
				count++;
				prev = arr[i];
			}
		}
		if (count >= c){              //如果count个牛比c个牛多，那么修改left，使mid增大
			result = mid;
			left = mid + 1;
		}
		else {
			right = mid - 1;          //反之修改right，使mid减小
		}
	}
	cout << result << endl;
	return 0;
}
