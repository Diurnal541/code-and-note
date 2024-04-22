#include <iostream>
using namespace std;
int vis[100];
int main(){
	int n,s = 0;
	cin >> n;
	for (int i = 0;i < n;i++){
		for (int j = 0;j < 3;j++){
			s++;
			if (s > n){
				s = 1;
			}
			if (vis[s]){
				j--;
			}
		}
		vis[s] = 1;
	}
	cout << s << endl;
	return 0;
}
