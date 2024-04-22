#include<iostream>
#include<cstring>
using namespace std;
int main(){
	string s;
	bool flag = true;
	cin >> s;
	int l = s.size();
	for (int i = 0;i < l;i++){
		for (int j = i + 1;j < l;j++){
			if (s[i] == s[j]){
				flag = false;
			}
		}
	}
	if (flag){
		cout << "YES" << endl;
	}
	else{
		cout << "NO" << endl;
	}
	return 0;
}

