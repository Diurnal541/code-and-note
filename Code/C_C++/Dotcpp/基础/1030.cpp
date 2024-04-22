#include <iostream>
using namespace std;
int a[10][10];
int main(){
	for (int i = 0;i < 3;i++){
		for (int j = 0;j < 3;j++){
			cin >> a[i][j];
		}
	}
	for (int i = 0;i < 3;i++){
		for (int j = 0;j < 3;j++){
			cout << a[j][i] << " ";
			if (j == 2){
				cout << endl;
			}
		}
	}
	return 0;
}
