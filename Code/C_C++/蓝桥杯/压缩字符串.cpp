#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
	string str1,str2 = "";
	int count = 1;
	cin >> str1;
	sort(str1.begin(),str1.end());
	for (int i = 0;i < str1.size();i++){
		if (str1[i] == str1[i + 1]){
			count++;
		}
		else{
			str2 += str1[i];
			if (count > 1){
				str2 += to_string(count);
			}
			count = 1;
		}
	}
	int len1 = str1.size(),len2 = str2.size();
	if (len1 > len2){
		cout << str2 << endl;
	}
	else{
		cout << "NO" << endl;
	}
	return 0;
}
