#include <iostream>
using namespace std;
int main()
{
	int a,b;
	cin >> a >> b;
	if (a == b)
	{
		cout << 0 << endl;
	}
	else if (a == 0)
	{
		if (b == 1)
		{
			cout << -1 << endl;
		}
		else 
		{
			cout << 1 << endl;
		}
	}
	else if (a == 1)
	{
		if (b == 0)
		{
			cout << 1 << endl;
		}
		else 
		{
			cout << -1 << endl;
		}
	}
	else
	{
		if (b == 1)
		{
			cout << 1 << endl;
		}
		else 
		{
			cout << -1 << endl;
		}
	}
	return 0;
}
/*
#include<bits/stdc++.h>
using namespace std;
int main(){
    int a, b; cin >> a >> b;
    if(a == 2 && b == 1 || a == 1 && b == 0 || a == 0 &&b == 2) cout<< "1" <<endl;
    else if(a == b) cout << "0" << endl;
    else cout << "-1" << endl;
    return 0;
}
*/ 
