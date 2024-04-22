#include <iostream>
#include <string>
using namespace std;
void rev(const string& s,string& n){
	n = s;
	for (int i = 0;i < n.length() / 2;i++){
		swap(n[i],n[n.length() - i - 1]);
	}
}
int main(){
	string s,n = "";
	cin >> s;
	rev(s,n);
	cout << n << endl;
	return 0;
}
