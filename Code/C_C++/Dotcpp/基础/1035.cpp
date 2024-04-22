#include <iostream>
#include <string>
using namespace std;
int num_alpha = 0,num_digit = 0,num_space = 0,num_other = 0;
void count(string a){
	for (int i = 0;i < a.length();i++){
		if (isalpha(a[i])){
			num_alpha++;
		}
		else if (isdigit(a[i])){
			num_digit++;
		}
		else if (isspace(a[i])){
			num_space++;
		}
		else {
			num_other++;
		}
	}
}
int main(){
	string a;
	getline(cin,a);
	count(a);
	cout << num_alpha << " " << num_digit << " " << num_space << " " << num_other << endl;
	return 0;
}
