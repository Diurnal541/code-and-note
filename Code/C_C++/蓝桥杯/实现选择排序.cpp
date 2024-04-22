#include<iostream>
#include<vector>
using namespace std;
int main(){
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0;i < n;i++){
		cin >> arr[i];
	}
	int start = 0,end = n - 1;
	while (start < end){
		int min = start;
		int max = start;
		for (int i = start;i <= end;i++){
			if (arr[i] < arr[min]){
				min = i;
			}
			if (arr[i] > arr[max]){
				max = i;
			}
		}
		int temp = arr[min];
		arr[min] = arr[start];
		arr[start] = temp;
		if (start == max){
			max = min;
		}
		temp = arr[max];
		arr[max] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
	for (int i = 0;i < n;i++){
		cout << arr[i] << " ";
	}
	return 0;
}
