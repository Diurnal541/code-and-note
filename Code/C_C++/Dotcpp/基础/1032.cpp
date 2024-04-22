#include <iostream>
#include <string>
using namespace std;
void conn(string& a,string& b){
	a += b;
}
int main(){
	string a,b;
	cin >> a >> b;
	conn(a,b);
	cout << a << endl;
	return 0;
}
