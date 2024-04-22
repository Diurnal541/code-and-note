#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;
int main(){
	char op;
	int a,b,c,ans = 0,k;
	while (~(k = scanf("%d%c%d=%d",&a,&op,&b,&c))){
		if (k == 4){
			if (op == '+' && c == a + b){
				ans++;
			}
			else if (op == '-' && c == a - b){
				ans++;
			}			
		}
		else {
			getchar();
		}
	}
	cout << ans << endl;
	return 0;
}
