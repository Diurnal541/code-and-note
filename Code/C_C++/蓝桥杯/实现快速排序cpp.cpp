#include<iostream>
#include<vector>
using namespace std;
int part(int*,int,int);
void quicksort(int*,int,int);
int main(){
	int n;
	cin >> n;
	int r[100];
	for (int i = 0;i < n;i++){
		cin >> r[i];
	}
	quicksort(r,0,n);
	for (int i = 0;i < n;i++){
		cout << r[i] << " ";
	}
	return 0;
}
int part(int *r,int low,int hight){
	int i = low,j = hight,pivot = r[low];
	while (i < j){
		while (i < j && r[j] > pivot){
			j--;
		}
		if (i < j){
			swap(r[i],r[j]);
			i++;
		}
		while (i < j && r[i] <= pivot){
			i++;
		}
		if (i < j){
			swap(r[i],r[j]);
			j++;
		}
	}
	return i;
}
void quicksort(int *r,int low,int hight){
	int mid;
	if (low < hight){
		mid = part(r,low,hight);
		quicksort(r,low,mid - 1);
		quicksort(r,mid + 1,hight);
	}
}
