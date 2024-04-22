#include <iostream>
#include <string>
using namespace std;
int m,n;
char ch[100];
int main(){
	cin >> n;
	for (int i = 0;i < n;i++){
		cin >> ch[i];
	}
	cin >> m;
	for (int i = m - 1;i < n;i++){
		cout << ch[i];
	}
	return 0;
}
