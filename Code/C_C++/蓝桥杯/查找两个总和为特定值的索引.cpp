#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
	int n,s;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0;i < n;i++){
		cin >> arr[i];
	}
	cin >> s;
	for (int i = 0;i < n;i++){
		for (int j = i + 1;j < n;j++){
			if (arr[i] + arr[j] == s){
				cout << i << " " << j << endl;
				return 0;
			}
		}
	}
	return 0;
}
