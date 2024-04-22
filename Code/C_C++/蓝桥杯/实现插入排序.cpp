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
	for(int j = 0; j< n - 1; j++)
	{
		int end = j;  
		int temp = arr[j + 1];
		while(end >= 0)
		{
			if(arr[end] > temp)   
			{
				arr[end + 1]=arr[end];  
				end--;   
			}
			else 
			{
				break;
			}
		}
		arr[end + 1]=temp;
	}
	for (int i = 0;i < n;i++){
		cout << arr[i] << " ";
	}
	return 0;
}