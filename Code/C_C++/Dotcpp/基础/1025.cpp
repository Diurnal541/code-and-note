#include <iostream>
using namespace std;
int arr[100];
int n,index;
int main(){
	for (int i = 0;i < 9;i++){
		cin >> arr[i];
	}
	cin >> n;
	for (int i = 0;i < 9;i++){
		if (n >= arr[i]){
			continue;
		}
		else{
			index = i;
			break;
		}
	}
	for (int i = 9;i >= index;i--){
		arr[i] = arr[i - 1];
	}
	arr[index] = n;
	for (int i = 0;i < 10;i++){
		cout << arr[i] << " ";
	}
	return 0;
}
