#include<iostream>
#include<cstring>
using namespace std;
int main(){
	char s1[100],s2[100];
	cin >> s1 >> s2;
	int sum1 = 0,sum2 = 0;
	for (int i = 0;i < strlen(s1);i++){
		sum1 += s1[i];
	}
	for (int i = 0;i < strlen(s2);i++){
		sum2 += s2[i];
	}
	cout << char(abs(sum1 - sum2)) << endl;
	return 0;
}
