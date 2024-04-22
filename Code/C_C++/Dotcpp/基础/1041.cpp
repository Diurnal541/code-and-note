#include <iostream>
#include <cstdio>
using namespace std;
#define search_max(x1,x2,x3) x1 > x2 ? (x1 > x3 ? x1 : x3) : (x2 > x3 ? x2 : x3)
float Max(float m,float n){
	if (m > n){
		return m;
	}
	else{
		return n;
	}
}
int main(){
	float x1,x2,x3;
	cin >> x1 >> x2 >> x3;
	printf("%.3f\n",search_max(x1,x2,x3));
	printf("%.3f\n",Max(x1,Max(x2,x3)));
	return 0;
}
