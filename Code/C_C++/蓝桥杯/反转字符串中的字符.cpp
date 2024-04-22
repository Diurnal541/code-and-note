#include<iostream>
#include<string>
using namespace std;
int main(){
	string str1,str2;
	getline(cin,str1);
	int len = str1.size();
	for (int i = len - 1;i >= 0;i--){
		str2.push_back(str1[i]);
	}
	cout << str2 << endl;
	return 0;
}
