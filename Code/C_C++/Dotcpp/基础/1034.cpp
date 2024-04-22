#include <iostream>
using namespace std;
void des(string a){
	for (int i = 0;i < a.length();i++){
		cout << a[i] << " ";
	}
}
int main(){
	string a;
	cin >> a;
	des(a);
	return 0;
}
