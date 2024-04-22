#include <iostream>
#include <cstring>
using namespace std;
int main(){
	string s;
	getline(cin,s);
	for (int i = 0;i < s.length();i++){
		if (isalpha(s[i])){
			if (s[i] == 'z'){
				s[i] = 'a';
			}
			else{
				s[i] += 1;
			}
		}
		else{
			continue;
		}
	}
	cout << s << endl;
	return 0;
}
