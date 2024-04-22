#include<iostream>
using namespace std;
int search(int*,int,int);
int main(){
	int data[200];
	for (int i = 0;i < 200;i++){
		data[i] = 4 * i + 6;
	}
	int target;
	cin >> target;
	int index = search(data,200,target);
	if (index){
		cout << index << endl;
	}
	else{
		cout << "WRONG" << endl;
	}
	return 0;
}
int search(int *data,int size,int target){
	int left = 0;
	int right = size - 1;
	while (left <= right){
		int mid = (left + right) / 2;
		if (data[mid] > target){
			right = mid - 1;
		}
		else if (data[mid] < target){
			left = mid + 1;
		}
		else{
			return mid;
		}
	}
	return -1;
}
