#include <iostream>
using namespace std;
void vowel(string& a,string& b){
	for (int i = 0;i < a.length();i++){
		if (a[i] == 'a' || a[i] == 'e' || a[i] == 'i' || a[i] == 'o' || a[i] == 'u'){
			b += a[i];
		}
	}
}
int main(){
	string a,b = "";
	cin >> a;
	vowel(a,b);
	cout << b << endl;
	return 0;
}
