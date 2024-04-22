#include <iostream>
using namespace std;
void input(int arr[]){
	for (int i = 0;i < 10;i++){
		cin >> arr[i];
	}
}
void change(int arr[]){
	int max = 0,min = 0;
	for (int i = 0;i < 10;i++){
		if (arr[i] > arr[max]){
			max = i;
		}
		if (arr[i] < arr[min]){
			min = i;
		}
	}
	int temp = arr[max];
	arr[max] = arr[9];
	arr[9] = temp;
	temp = arr[min];
	arr[min] = arr[0];
	arr[0] = temp;
}
void output(int arr[]){
	for (int i = 0;i < 10;i++){
		cout << arr[i] << " ";
	}
}
int arr[10];
int main(){
	input(arr);
	change(arr);
	output(arr);
	return 0;
}
