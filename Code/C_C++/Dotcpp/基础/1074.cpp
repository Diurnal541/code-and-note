#include <iostream>
using namespace std;
int main(){
	char s[200];
	while (cin >> s){
		if (s[0] == '0'){
			break;
		}
		else{
			int num = 0;
			for (int i = 0;s[i] != '\0';i++){
				num = num * 10 + s[i] - '0';
				num %= 17;
			}
			if (num == 0){
				cout << 1 << endl;
			}
			else{
				cout << 0 << endl;
			}
		}
	}
	return 0;
}
